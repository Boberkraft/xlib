cmake_minimum_required(VERSION 3.17)
project(xlib)

set(CMAKE_CXX_STANDARD 20)

add_executable(xlib main.cpp)

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})
target_link_libraries(xlib ${X11_LIBRARIES})

