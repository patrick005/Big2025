cmake_minimum_required(VERSION 3.00)
project(bowling)

# 헤더 파일 경로 설정
include_directories(include)

# 소스 파일 경로 설정
set(SOURCES
    src/bowling.c
    src/main.c
    src/score.c
)
# 실행 파일 생성
add_executable(bowling ${SOURCES})

# MySQL 헤더 및 라이브러리 경로 설정
target_include_directories(bowling PRIVATE /usr/include/mysql)
target_link_directories(bowling PRIVATE /usr/lib/mysql)
target_link_libraries(bowling PRIVATE mysqlclient)
target_link_directories(bowling PRIVATE /usr/local/bin)
target_link_libraries(bowling PRIVATE dotenv)



# target_include_directories(bowling PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)

# message(STATUS "Using compiler: ${CMAKE_C_COMPILER}")
# message(STATUS "Include directories: /usr/include/mysql")
# message(STATUS "Library directories: /usr/lib/mysql")
# 컴파일 디버그용 메시지 출력