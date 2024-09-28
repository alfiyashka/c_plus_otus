cmake_minimum_required(VERSION 3.28.3)



set(PATCH_VERSION "1" CACHE INTERNAL "PATCH_VERSION" )
set(PROJECT_VERSION 0.0.${PATCH_VERSION})


project(hw4 VERSION ${PROJECT_VERSION} LANGUAGES C CXX)


configure_file(version.h.in version.h)

include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})


add_executable(hw4 main.cpp)

set_property(TARGET hw4 PROPERTY CXX_STANDARD 17)


include("functions.cmake")
generate_packages(${PROJECT_NAME})

