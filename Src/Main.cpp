
#include <filesystem>
#include <iostream>
#include <Windows.h>
#include <LFramework/COM/ComObject.h>
#include <LFramework/COM/ComLibrary.h>

typedef void (LFRAMEWORK_COM_LIBRARY_CALL *getInterface)(LFramework::ComPtr<LFramework::IUnknown>& result);
int main() {

    
    HMODULE lib = LoadLibraryA("Dependencies/MicroNetwork.Library/MicroNetwork.dll");

    void* getInterfaceFunc = GetProcAddress(lib, "getInterface");
    auto getInterfacePtr = reinterpret_cast<getInterface>(getInterfaceFunc);

    LFramework::ComPtr<LFramework::IUnknown> ilib;
    getInterfacePtr(ilib);


    
  
    std::cout << std::filesystem::current_path() << std::endl;
    return 0;
}