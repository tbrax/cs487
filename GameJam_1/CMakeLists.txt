cmake_minimum_required(VERSION 3.13)
#set(CMAKE_CXX_COMPILER "/bin/g++-9")
project(cs487game)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(gamelib)
add_subdirectory(simplegame)

