
#include <filesystem>
#include <iostream>
#include <Windows.h>
#include <LFramework/COM/ComObject.h>
#include <LFramework/COM/ComLibrary.h>

#include <MicroNetwork.Task.MemoryAccess.IStream.IoStreamDescriptor.h>
#include <MicroNetwork.Host.h>

#include <McuControlImpl.h>
#include <MicroNetwork/User/LinkConstructor.h>

#include <thread>
#include <chrono>

typedef void (LFRAMEWORK_COM_LIBRARY_CALL *getInterface)(LFramework::ComPtr<LFramework::IUnknown>& result);
int main() {

    
    HMODULE lib = LoadLibraryA("Dependencies/MicroNetwork.Library/MicroNetwork.dll");

    void* getInterfaceFunc = GetProcAddress(lib, "getInterface");
    auto getInterfacePtr = reinterpret_cast<getInterface>(getInterfaceFunc);

    LFramework::ComPtr<LFramework::IUnknown> ilibUnknown;
    getInterfacePtr(ilibUnknown);

    auto ilibrary = ilibUnknown.queryInterface<MicroNetwork::Host::ILibrary>();

    auto network = ilibrary->createNetwork(0x0301, 0x1111);

    auto updateId = 0;
    
    while(true){
        auto id = network->getStateId();
        if(id != updateId){
            updateId = id;
            std::cout << "New update ID: " << id << std::endl;

            auto nodes = network->getNodes();
            for(auto node : nodes){
                auto mcuControlId = LFramework::getInterfaceId<MicroNetwork::Task::MemoryAccess::IStream>();
                if(network->isTaskSupported(node, mcuControlId)){
                    std::cout << "Found McuControl device" << std::endl;

                    auto mcuControlTask = MicroNetwork::User::LinkConstructor<McuControl::IMcuControl, McuControl::Impl>::constructLink(network, node);

                    while(mcuControlTask->isConnected()){
                        mcuControlTask->readMemory();
                        std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    }
                    std::cout << "McuControl task finished" << std::endl;
                }else{
                    std::cout << "Found NOT McuControl device" << std::endl;
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
   


    std::cout << std::filesystem::current_path() << std::endl;
    return 0;
}