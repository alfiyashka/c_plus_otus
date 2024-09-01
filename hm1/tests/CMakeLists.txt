cmake_minimum_required(VERSION 3.28.3)

set(HW1_UNIT_TESTS 
hw1BoostTest.cpp)

include_directories(..)

set(CMAKE_CXX_STANDARD 17)

add_executable (HW1Test_run ${HW1_UNIT_TESTS})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

target_link_libraries(HW1Test_run ${Boost_LIBRARIES})

add_test(helloworld HW1Test_run)