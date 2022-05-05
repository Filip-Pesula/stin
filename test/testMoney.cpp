#define BOOST_TEST_MODULE DummyTest
#include <boost/test/included/unit_test.hpp>

#include <Money.h>
#include <Logger.h>
BOOST_AUTO_TEST_CASE(test_Money_getString_Nominal){
    Money euro(20,5);
    BOOST_CHECK(euro.to_string<char32_t>(U",") == std::u32string(U"20,05"));
    Logger::log(euro.to_string<char32_t>(U","));
    Logger::log(euro.to_string<char32_t>(U",").size());
    Logger::log(std::u32string(U"20,05").size());
}

BOOST_AUTO_TEST_CASE(test_Money_getString_0Cents){
    Money euro(20,0);
    BOOST_CHECK(euro.to_string<char32_t>(U",") == std::u32string(U"20,00"));
    Logger::log(euro.to_string<char32_t>(U","));
}

BOOST_AUTO_TEST_CASE(test_Money_getString_0Units){
    Money euro(0,20);
    BOOST_CHECK(euro.to_string<char32_t>(U",") == std::u32string(U"0,20"));
    Logger::log(euro.to_string<char32_t>(U","));
}

BOOST_AUTO_TEST_CASE(test_Money_getFromString){
    Money<> m(Money<>::getFromString("15,257"));
    BOOST_CHECK_EQUAL(m.getCents(),1525);
}

BOOST_AUTO_TEST_CASE(test_Money_throws){
    BOOST_CHECK_THROW(Money<>::getFromString("15,25"),std::invalid_argument);
    BOOST_CHECK_THROW(Money<>::getFromString("1a,250"),std::invalid_argument);
    BOOST_CHECK_THROW(Money<>::getFromString("15,2a0"),std::invalid_argument);
    BOOST_CHECK_THROW(Money<>::getFromString(""),std::invalid_argument);
    BOOST_CHECK_THROW(Money<>::getFromString("15.2a0"),std::invalid_argument);
    BOOST_CHECK_THROW(Money<>::getFromString("1q.2q0"),std::invalid_argument);
}