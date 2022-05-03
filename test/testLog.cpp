#define BOOST_TEST_MODULE TestLogger
#include <boost/test/included/unit_test.hpp>

#include <Logger.h>
#include <codecvt>
#include <locale>

struct TestFixture{
    std::ostringstream oss;
    std::streambuf* p_cout_streambuf;
    TestFixture(){
        p_cout_streambuf = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());
    }
};

BOOST_FIXTURE_TEST_CASE( test_getKeySets, TestFixture )
{
    BOOST_CHECK(1 == 1);
}

BOOST_FIXTURE_TEST_CASE(test_Log_string,TestFixture){


    Logger::log(std::string("test text"));

    std::cout.rdbuf(p_cout_streambuf); // restore

    BOOST_CHECK(oss && oss.str() == "test text\n");
}


BOOST_FIXTURE_TEST_CASE(test_Log_u32strig_t,TestFixture){
    std::u32string str = U"testText: awdsdfw+ěščřřážéý";
    Logger::log(str);
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> utfConverter;
    std::cout.rdbuf(p_cout_streambuf); // restore

    BOOST_CHECK_EQUAL(oss.str() , utfConverter.to_bytes(str+U"\n") );
}

BOOST_FIXTURE_TEST_CASE(test_Log_date,TestFixture){
    std::string date_s = "2000-04-20";
    boost::gregorian::from_simple_string(date_s);
    boost::gregorian::date date = boost::gregorian::from_simple_string("2000-04-20");
    Logger::log(date);
    std::string expect("20-04-2000\n");
    std::cout.rdbuf(p_cout_streambuf); // restore
    BOOST_CHECK_EQUAL(oss.str() , "2000-04-20\n");
}

BOOST_FIXTURE_TEST_CASE(test_Log_u32strig_view_t,TestFixture){
    std::u32string str = U"testText: awdsdfw+ěščřřážéý";
    std::u32string_view str_view(str.c_str());
    Logger::log(str_view);
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> utfConverter;
    std::cout.rdbuf(p_cout_streambuf); // restore

    BOOST_CHECK_EQUAL(oss.str() , utfConverter.to_bytes(str+U"\n") );
}