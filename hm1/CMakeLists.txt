cmake_minimum_required(VERSION 3.28.3)

set(PATCH_VERSION "1" CACHE INTERNAL "PATCH_VERSION" )
set(PROJECT_VERSION 0.0.${PATCH_VERSION})


project(helloworld VERSION ${PROJECT_VERSION} LANGUAGES C CXX)

configure_file(version.h.in version.h)

include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

add_executable(helloworld main.cpp)

set_property(TARGET helloworld PROPERTY CXX_STANDARD 17)

option(WITH_BOOST_TEST "Enable using BOOST_TEST" ON)

if (WITH_BOOST_TEST)
    enable_testing()
    add_subdirectory(tests)

endif()

include(CPack)

