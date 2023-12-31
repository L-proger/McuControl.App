cmake_minimum_required(VERSION 3.16)
project(ApiGenerator)
add_subdirectory(ComInterfaceGenerator)

set(ApiIncludeDirs 
    "../Dependencies/MicroNetwork.Library/Dependencies/MicroNetworkCommon/Api"
    "../Dependencies/MicroNetwork.Library/Dependencies/MicroNetworkHost/Api"
    "../Dependencies/McuControl.Library/Api"
    "../Dependencies/MicroNetworkUser/Api"
)



set(ApiOutputDir "../Interfaces")
set(ApiOutputLanguage "Cpp")
set(ApiEnableExceptions ON)
set(ApiOutputModules "McuControl" "MicroNetwork.Common" "MicroNetwork.Host" "MicroNetwork.Task.MemoryAccess" "MicroNetwork.User")

ComInterfaceGeneratorMakeArgs( OUTMODULES ${ApiOutputModules} RESULT_VAR "GenerateApiArgs" )

set(ApiInInterfaces "MicroNetwork.Task.MemoryAccess.IDeviceToHost")
ComInterfaceGeneratorMakeArgs( OUTMODULES ${ApiInInterfaces} RESULT_VAR "GenerateApiInSerializersArgs" )

set(ApiOutInterfaces "MicroNetwork.Task.MemoryAccess.IHostToDevice")
ComInterfaceGeneratorMakeArgs( OUTMODULES ${ApiOutInterfaces} RESULT_VAR "GenerateApiOutSerializersArgs" )

ComInterfaceGeneratorMakeArgs( OUTMODULES "MicroNetwork.Task.MemoryAccess.IStream" RESULT_VAR "GenerateIoStreamDescriptorArgs" )

add_custom_target(GenerateApi
    COMMAND ${CMAKE_COMMAND} -E echo "-- Generating API"
    COMMAND $<TARGET_FILE:ComInterfaceGenerator> "generate" ${GenerateApiArgs}
    COMMAND ${CMAKE_COMMAND} -E echo "-- Generating API IN serializers"
    COMMAND $<TARGET_FILE:ComInterfaceGenerator> "generateInterfaceSerializer" -d "in" ${GenerateApiInSerializersArgs}
    COMMAND ${CMAKE_COMMAND} -E echo "-- Generating API OUT serializers"
    COMMAND $<TARGET_FILE:ComInterfaceGenerator> "generateInterfaceSerializer" -d "out" ${GenerateApiOutSerializersArgs}
    COMMAND ${CMAKE_COMMAND} -E echo "-- Generating IO stream descriptor"
    COMMAND $<TARGET_FILE:ComInterfaceGenerator> "generateIoStreamDescriptor"  ${GenerateIoStreamDescriptorArgs}
    VERBATIM
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

