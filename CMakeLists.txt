cmake_minimum_required(VERSION 2.6)
project(hw1)


set(CMAKE_CXX_STANDARD 14)
add_executable(hw1 main.cpp)

install(TARGETS hw1 RUNTIME DESTINATION bin)
