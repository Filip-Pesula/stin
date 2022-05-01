#define BOOST_TEST_MODULE UtilstTest
#include <boost/test/included/unit_test.hpp>
#include <utils.h>

BOOST_AUTO_TEST_CASE(testgen404){
    std::string str = STIN_Bot::gen404("/adr");
    std::string expect = 
"<!DOCTYPE html>\n\
<html lang=\"en\">\n\
<head>\n\
\t<meta charset=\"UTF-8\">\n\
\t<title>PAGE NOT FOUND</title>\n\
</head>\n\
<body>\n\
\t<header>\n\
\t404 Page: /adr Not Found\n\
\t</header>\n\
</body>\n\
</html>\n";
    BOOST_CHECK_EQUAL(str.size(), expect.size());
    BOOST_CHECK_EQUAL(str, expect);
}

BOOST_AUTO_TEST_CASE(test_now){
    std::cout<<STIN_Bot::now();
    std::time_t now = std::time(0);
    BOOST_CHECK_EQUAL(STIN_Bot::now(), std::time(0));
}