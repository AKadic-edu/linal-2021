cmake_minimum_required(VERSION 3.8)
project(linal)

enable_testing()
set(CMAKE_CXX_STANDARD 11)

add_subdirectory("mathlib")
add_subdirectory("videolib")

add_subdirectory("assignments/week1")
add_subdirectory("assignments/week2")
add_subdirectory("assignments/final")
