cmake_minimum_required (VERSION 3.15.0)

project(McuControlApp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

add_executable(McuControlApp)


add_subdirectory(Dependencies/MicroNetwork.Library)
add_subdirectory(Dependencies/McuControl.Library)
#add_subdirectory(Dependencies/MicroNetworkUser)


target_sources(McuControlApp 
PRIVATE 
	Src/Main.cpp
)

target_include_directories(McuControlApp 
PUBLIC 
	"${CMAKE_CURRENT_SOURCE_DIR}/Interfaces"
)


#target_compile_definitions(LFramework PUBLIC LF_USB_HOST)

target_link_libraries(McuControlApp 
PRIVATE 
	LFramework
	LFramework::UnitTest
	LFramework::IO
	LFramework::IO::Terminal
	McuControl::Library
	MicroNetworkUser
)

target_compile_definitions(McuControlApp 
INTERFACE 
	LF_THREAD_STD
	LF_TERMINAL_STREAM_COUT
)