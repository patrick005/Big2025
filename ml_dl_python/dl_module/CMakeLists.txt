cmake_minimum_required(VERSION 3.0)
project(zmq_example)

find_package(PkgConfig REQUIRED)
pkg_check_modules(ZMQ REQUIRED libzmq)

add_executable(zmq_server zmq_server.cpp)
target_link_libraries(zmq_server PRIVATE zmq)

add_executable(zmq_client zmq_client.cpp)
target_link_libraries(zmq_client PRIVATE zmq)