#define BOOST_TEST_MODULE testVersion

#include <boost/test/unit_test.hpp>

#include "version.h"

BOOST_AUTO_TEST_SUITE( check_version_test )

    BOOST_AUTO_TEST_CASE( version_test )
    {
        const std::string version(OTUS_HW1_VERSION);
        std::cout<<version.c_str() << std::endl;
        BOOST_CHECK( !version.empty() );
    }

BOOST_AUTO_TEST_SUITE_END()