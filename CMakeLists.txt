cmake_minimum_required (VERSION 3.15.0)

project(McuControlApp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

add_executable(McuControlApp)


add_subdirectory(Dependencies/MicroNetwork.Library)

target_sources(McuControlApp 
PRIVATE 
	Src/Main.cpp
)

#target_include_directories(libMicroNetwork PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Interfaces")


#target_compile_definitions(LFramework PUBLIC LF_USB_HOST)

#target_link_libraries(libMicroNetwork PRIVATE User32 Advapi32 Ole32 Winusb SetupAPI)