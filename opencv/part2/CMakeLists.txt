cmake_minimum_required(VERSION 3.0)
project(part2)

find_package(OpenCV REQUIRED)

file(GLOB SOURCES "*.cpp")

foreach(SOURCE ${SOURCES})
    get_filename_component(EXE_NAME ${SOURCE} NAME_WE)
    if(EXE_NAME STREQUAL "16_filestorage")
        add_executable(${EXE_NAME} ${SOURCE} array.cpp)
        target_link_libraries(${EXE_NAME} ${OpenCV_LIBS})
    elseif(EXE_NAME STREQUAL "array")
    else()
        add_executable(${EXE_NAME} ${SOURCE})
        target_link_libraries(${EXE_NAME} ${OpenCV_LIBS})
    endif()
endforeach()