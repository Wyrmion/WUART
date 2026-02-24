# CMakeLists.txt for the static library
cmake_minimum_required (VERSION 3.2...4.2)

set(LIB_NAME hwuart)


# Enable CMake support for C languages
enable_language(C ASM)

add_library(${LIB_NAME} STATIC UARTInterface.c STHallUartInterface.c RSxxx.c)


target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(${USE_WRS4XX_PIN})
    target_compile_definitions(${LIB_NAME} PUBLIC RS4XX_USE_HW_PIN W_USE_RTOS)
    
    add_subdirectory(RS4xxDEnRE rs4xxdenre)
    target_link_libraries(${LIB_NAME} PUBLIC wheap rs4xxdenre)
    
    target_link_libraries(rs4xxdenre PUBLIC hwpin maincpp) #maincpp for HALL driver
else()
    target_link_libraries(${LIB_NAME} PRIVATE wheap)
endif()

#if(${USE_INTERFACE_PARENT})
    set_property(DIRECTORY . APPEND PROPERTY COMPILE_DEFINITIONS "WINTERFACE_USE_INTERFACE_PARENT_LIB")
    target_link_libraries(${LIB_NAME} PRIVATE interface)
#endif()







