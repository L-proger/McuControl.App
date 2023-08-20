
#include <filesystem>
#include <iostream>
#include <Windows.h>
#include <LFramework/COM/ComObject.h>
#include <LFramework/COM/ComLibrary.h>

#include <MicroNetwork.Task.MemoryAccess.IStream.IoStreamDescriptor.h>
#include <MicroNetwork.Host.h>

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
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
   


    std::cout << std::filesystem::current_path() << std::endl;
    return 0;
}