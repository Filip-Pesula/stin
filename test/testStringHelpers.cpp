#define BOOST_TEST_MODULE TestStringHelpers
#include <boost/test/included/unit_test.hpp>
#include <StringHelpers.h>

BOOST_AUTO_TEST_CASE(test_format){
    BOOST_CHECK_EQUAL(
        stringWithFormat("%d", 3) 
        ,
        "3"
        );
    BOOST_CHECK_EQUAL(
        stringWithFormat("% 2d", 3) 
        ,
        " 3"
        );
    BOOST_CHECK_EQUAL(
        stringWithFormat("%02d", 3).size()
        ,
        2
        );
    BOOST_CHECK_EQUAL(
        stringWithFormat("%.1f", 1.2f) 
        , 
        "1.2"
        );
}