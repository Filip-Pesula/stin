#define BOOST_TEST_MODULE TestRequest
#include <boost/test/included/unit_test.hpp>
#include <Request.h>
using namespace STIN_Bot;

class TestableRequest : public Request{
public:
    std::vector<KeySet> getKeysets() const override {
        return std::vector<KeySet>(
            { 
               KeySet({U"jaký",U"what"}) ,
               KeySet({U"čas",U"time"})
            }
        );
    }
    std::u32string getResponse() const override {
        return std::u32string(U"time is: now");
    }
};
/*
{ 
    {U"jak",U"how"},
    {U"se",U"are"},
    {U"máš",U"you",U"u"}
}
*/
struct TestFixture{
    TestFixture(){}
    TestableRequest request;
};

BOOST_FIXTURE_TEST_CASE( test_getKeySets, TestFixture )
{
    std::vector<KeySet> keysets(std::move(request.getKeysets()));
    BOOST_CHECK_EQUAL( keysets.size() ,2);
}