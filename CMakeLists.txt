cmake_minimum_required(VERSION 3.10)
project(MainProject)

# 내부 CMakeLists.txt 포함
add_subdirectory(sqlQuery)
add_subdirectory(c_example/part1)
add_subdirectory(c_example/part2)
add_subdirectory(c_example/part3)
add_subdirectory(Bowling)
# add_subdirectory(ds)
add_subdirectory(cpp)
add_subdirectory(STL)