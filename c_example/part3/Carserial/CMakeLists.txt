cmake_minimum_required(VERSION 3.10)
project(Carserial)

set (SOURCES
main.c
serial.c
)

# include_directories((${CMAKE_CURRENT_LIST_DIR}/include)) 필요한 폴더가 있을 경우
add_executable(Carserial main.c serial.c)
