#define BOOST_TEST_MODULE TestLogger
#include <boost/test/included/unit_test.hpp>

#include <Logger.h>
#include <codecvt>
#include <locale>

BOOST_AUTO_TEST_CASE(test_Log_string){
    std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    Logger::log(std::string("test text"));

    std::cout.rdbuf(p_cout_streambuf); // restore

    BOOST_CHECK(oss && oss.str() == "test text\n");
}


BOOST_AUTO_TEST_CASE(test_Log_u32strig_t){
    std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    std::u32string str = U"testText: awdsdfw+ěščřřážéý";
    Logger::log(str);
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> utfConverter;
    std::cout.rdbuf(p_cout_streambuf); // restore

    BOOST_CHECK_EQUAL(oss.str() , utfConverter.to_bytes(str+U"\n") );
}

BOOST_AUTO_TEST_CASE(test_Log_u32strig_view_t){
    std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    std::u32string str = U"testText: awdsdfw+ěščřřážéý";
    std::u32string_view str_view(str.c_str());
    Logger::log(str_view);
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> utfConverter;
    std::cout.rdbuf(p_cout_streambuf); // restore

    BOOST_CHECK_EQUAL(oss.str() , utfConverter.to_bytes(str+U"\n") );
}