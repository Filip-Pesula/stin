#define BOOST_TEST_MODULE testResourceData
#include <boost/test/included/unit_test.hpp>
#include <ResourceData.h>


BOOST_AUTO_TEST_CASE(test_getTypeTesxt){
    std::string html = STIN_Bot::ResourceData::getTypeTesxt(STIN_Bot::HtmlType::html);
    std::string css = STIN_Bot::ResourceData::getTypeTesxt(STIN_Bot::HtmlType::css);
    std::string js = STIN_Bot::ResourceData::getTypeTesxt(STIN_Bot::HtmlType::js);
    std::string plain = STIN_Bot::ResourceData::getTypeTesxt(STIN_Bot::HtmlType::plain);
    std::string def = STIN_Bot::ResourceData::getTypeTesxt((STIN_Bot::HtmlType)-1);
    BOOST_CHECK_EQUAL(html,"text/html");
    BOOST_CHECK_EQUAL(css,"text/css");
    BOOST_CHECK_EQUAL(js,"text/javascript");
    BOOST_CHECK_EQUAL(plain,"text/plain");
    BOOST_CHECK_EQUAL(def,"text/plain");
}   
