cmake_minimum_required(VERSION 3.28.3)

project(homework1 VERSION 1.0.0 LANGUAGES C CXX)

include(GoogleTest)
enable_testing()

add_executable(homework1 main.cpp)

set_property(TARGET homework1 PROPERTY CXX_STANDARD 17)
