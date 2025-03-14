cmake_minimum_required(VERSION 3.00)
project(bookSql)

set(SOURCES
    src/bookSql.c
    src/main.c
    )

add_executable(bookSql ${SOURCES})
target_include_directories(bookSql PRIVATE include)
# target_include_directories(bookSql PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)

target_include_directories(bookSql PRIVATE /usr/include/mysql)
target_link_directories(bookSql PRIVATE /usr/lib/mysql)
target_link_libraries(bookSql PRIVATE mysqlclient)

# message(STATUS "Using compiler: ${CMAKE_C_COMPILER}")
# message(STATUS "Include directories: /usr/include/mysql")
# message(STATUS "Library directories: /usr/lib/mysql")
# 컴파일 디버그용 메시지 출력