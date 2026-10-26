# CMakeLists.txt for the static library
cmake_minimum_required (VERSION 3.2...4.2)

set(LIB_NAME wuart)


# Enable CMake support for C languages
enable_language(C ASM)

add_library(${LIB_NAME} STATIC UARTInterface.c STHallUartInterface.c RSxxx.c)


target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(W_RSXXX_USE_HW_PIN)
    target_compile_definitions(${LIB_NAME} PUBLIC W_RSXXX_USE_HW_PIN)
    
    add_subdirectory(RS4xxDEnRE)
    target_link_libraries(${LIB_NAME} PUBLIC rs4xxdenre)
    

endif()

target_link_libraries(${LIB_NAME} PRIVATE wheap stm32cubemx)

#if(${USE_INTERFACE_PARENT})
    set_property(DIRECTORY . APPEND PROPERTY COMPILE_DEFINITIONS "WINTERFACE_USE_INTERFACE_PARENT_LIB")
    target_link_libraries(${LIB_NAME} PRIVATE interface)
#endif()







