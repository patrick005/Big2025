cmake_minimum_required(VERSION 3.00)
project(Bowling)

set(SOURCES
    src/bowling.c
    src/main.c
    )

add_executable(bowling ${SOURCES})
target_include_directories(bowling PRIVATE include)
# target_include_directories(bowling PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)

target_include_directories(bowling PRIVATE /usr/include/mysql)
target_link_directories(bowling PRIVATE /usr/lib/mysql)
target_link_libraries(bowling PRIVATE mysqlclient)

# message(STATUS "Using compiler: ${CMAKE_C_COMPILER}")
# message(STATUS "Include directories: /usr/include/mysql")
# message(STATUS "Library directories: /usr/lib/mysql")
# 컴파일 디버그용 메시지 출력