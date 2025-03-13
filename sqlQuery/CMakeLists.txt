cmake_minimum_required(VERSION 3.00)
project(bookSql)

set(CMAKE_C_COMPILER "/usr/bin/gcc")

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(bookSql sqlQuery/bookSql.c)
target_include_directories(bookSql PRIVATE /usr/include/mysql)
target_link_directories(bookSql PRIVATE /usr/lib/mysql)
target_link_libraries(bookSql PRIVATE mysqlclient)

# target_link_libraries(bookSql PRIVATE mysql)

message(STATUS "Using compiler: ${CMAKE_C_COMPILER}")
message(STATUS "Include directories: /usr/include/mysql")
message(STATUS "Library directories: /usr/lib/mysql")
# 컴파일 디버그용 메시지 출력