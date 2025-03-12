cmake_minimum_required(3.00)
project(bookSql)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_COMPILE_FEATURES ON)

add_executable(bookSql bookSql.c)
target_include_directories(bookSql PRIVATE /usr/include/mysql)
target_link_directories(bookSql PRIVATE /usr/lib/mysql)
target_link_libraries(bookSql PRIVATE mysqlclient)