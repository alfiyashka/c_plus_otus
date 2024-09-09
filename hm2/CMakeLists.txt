cmake_minimum_required(VERSION 3.28.3)



set(PATCH_VERSION "1" CACHE INTERNAL "PATCH_VERSION" )
set(PROJECT_VERSION 0.0.${PATCH_VERSION})


project(hw2 VERSION ${PROJECT_VERSION} LANGUAGES C CXX)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ip_filter.tsv
 ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)


configure_file(version.h.in version.h)

include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

set(HW2_INCLUDES 
   src/IpAddressSorter.hpp
)

set(HW2_SRC 
   src/IpAddressSorter.cpp
)

add_executable(hw2 ${HW2_INCLUDES} ${HW2_SRC} main.cpp)

set_property(TARGET hw2 PROPERTY CXX_STANDARD 17)


include("functions.cmake")
generate_packages(${PROJECT_NAME})

