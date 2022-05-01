#define BOOST_TEST_MODULE TestKeySet
#include <boost/test/included/unit_test.hpp>
#include <Request.h>
using namespace STIN_Bot;
BOOST_AUTO_TEST_CASE(test_key_set_caontains_Nominal){
    KeySet keyset({ U"ano",U"ne",U"škoda" });
    std::u32string expect1(U"ano");
    std::u32string expect2(U"ne");
    std::u32string expect3(U"škoda");
    std::u32string nExpect1(U"Heh");
    BOOST_CHECK_EQUAL(keyset.contains(expect1) , true);
    BOOST_CHECK_EQUAL(keyset.contains(expect2) , true);
    BOOST_CHECK_EQUAL(keyset.contains(expect3) , true);
    BOOST_CHECK_EQUAL(keyset.contains(nExpect1) , false);

    BOOST_CHECK_EQUAL(keyset.contains(std::u32string_view(expect1.c_str())) , true);
    BOOST_CHECK_EQUAL(keyset.contains(std::u32string_view(expect2.c_str())) , true);
    BOOST_CHECK_EQUAL(keyset.contains(std::u32string_view(expect3.c_str())) , true);
    BOOST_CHECK_EQUAL(keyset.contains(std::u32string_view(nExpect1.c_str())) , false);

}