cmake_minimum_required(VERSION 3.28.3)



set(PATCH_VERSION "1" CACHE INTERNAL "PATCH_VERSION" )
set(PROJECT_VERSION 0.0.${PATCH_VERSION})


project(hw3 VERSION ${PROJECT_VERSION} LANGUAGES C CXX)


configure_file(version.h.in version.h)

include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

set(HW3_INCLUDES 
   src/CustomAllocator.hpp
   src/CustomMap.hpp
   src/CustomNode.hpp
   src/CustomMapIterator.hpp
)

add_executable(hw3 ${HW3_INCLUDES} main.cpp)

set_property(TARGET hw3 PROPERTY CXX_STANDARD 17)


include("functions.cmake")
generate_packages(${PROJECT_NAME})

