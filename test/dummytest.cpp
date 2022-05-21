#define BOOST_TEST_MODULE DummyTest
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_Log_string){
    BOOST_CHECK(1 == 1);
}

struct TestFixture{
    TestFixture(){}
};

BOOST_FIXTURE_TEST_CASE( test_getKeySets, TestFixture )
{
    BOOST_CHECK(1 == 1);
}


