
#include <filesystem>
#include <iostream>
#include <Windows.h>

int main() {

    
    HMODULE lib = LoadLibraryA("Dependencies/MicroNetwork.Library/MicroNetwork.dll");

    void* getInterfaceFunc = GetProcAddress(lib, "getInterface");

    //extern "C" LFRAMEWORK_COM_LIBRARY_EXPORT void LFRAMEWORK_COM_LIBRARY_CALL getInterface(LFramework::ComPtr<LFramework::IUnknown>& result)
    std::cout << std::filesystem::current_path() << std::endl;
    return 0;
}