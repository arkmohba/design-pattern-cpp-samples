cmake_minimum_required(VERSION 3.1)
project(template CXX)
FILE(GLOB sources *.cpp)
add_executable(main_app ${sources})