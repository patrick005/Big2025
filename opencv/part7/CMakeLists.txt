cmake_minimum_required(VERSION 3.0)
project(opencv/part7)

find_package(OpenCV REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(ZMQ REQUIRED libzmq)

add_executable(59_mnist_cnn 59_mnist_cnn.cpp)
target_link_libraries(59_mnist_cnn ${OpenCV_LIBS} ${ZMQ_LIBRARIES})

add_executable(60_google_vision 60_google_vision.cpp)
target_link_libraries(60_google_vision ${OpenCV_LIBS} ${ZMQ_LIBRARIES})