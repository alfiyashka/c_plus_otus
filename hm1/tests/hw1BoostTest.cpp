#define BOOST_TEST_MODULE testVersion

#include <boost/test/unit_test.hpp>

#include "version.h"

BOOST_AUTO_TEST_SUITE( check_version_test )

    BOOST_AUTO_TEST_CASE( version_test )
    {
        const std::string version(OTUS_HW1_VERSION);
        std::cout<<"Version " <<version.c_str() << std::endl;
        BOOST_CHECK_MESSAGE(!version.empty() , "version is empty! ");
    }

    BOOST_AUTO_TEST_CASE( version_test2 )
    {
        const std::string version(OTUS_HW1_VERSION);
        
        BOOST_CHECK_MESSAGE(std::strcmp(version.c_str(), "0.0.1") != 0,
           "version error: current version is " + version);
    }
BOOST_AUTO_TEST_SUITE_END()

