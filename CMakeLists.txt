cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(pws-engine VERSION 1.0 LANGUAGES CXX)


# c++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# dependencies
find_package(X11 REQUIRED)

message(STATUS "X11_FOUND = ${X11_FOUND}")
message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")

include_directories("${X11_INCLUDE_DIR}")

add_subdirectory(src)
