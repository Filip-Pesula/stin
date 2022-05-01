#define BOOST_TEST_MODULE TestBot
#include <boost/test/included/unit_test.hpp>

#include <Bot.h>
#include <Logger.h>

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


class TestableRequest2 : public Request{
public:
    std::vector<KeySet> getKeysets() const override {
        return std::vector<KeySet>(
            { 
                KeySet({U"jak",U"how"}),
                KeySet({U"se",U"are"}),
                KeySet({U"máš",U"you",U"u"})
            }
        );
    }
    std::u32string getResponse() const override {
        return std::u32string(U"good");
    }
};

struct TestFixture{
    std::vector<std::unique_ptr<Request>> makeRequests(){
        std::vector<std::unique_ptr<Request>> requests{
        };
        requests.push_back(std::move(std::make_unique<TestableRequest>()));
        requests.push_back(std::move(std::make_unique<TestableRequest2>()));
        return requests;
    }

    Bot bot;

    TestFixture():
        bot(std::move(makeRequests()))
    { 
    }
};


BOOST_FIXTURE_TEST_CASE(test_get_Request_Nominal_1, TestFixture){
    std::u32string response =  bot.processMessage(U"jak se máš");
    BOOST_CHECK(response == U"good");
    Logger::log("response:",response);
}

BOOST_FIXTURE_TEST_CASE(test_get_Request_Nominal_2, TestFixture){
    std::u32string response =  bot.processMessage(U"jaký je čas");
    BOOST_CHECK(response == U"time is: now");
    Logger::log("response:",response);
}

BOOST_FIXTURE_TEST_CASE(test_get_Request_Empty, TestFixture){
    std::u32string response =  bot.processMessage(U"");
    BOOST_CHECK(response == U"");
    Logger::log("response:",response);
}

BOOST_FIXTURE_TEST_CASE(test_get_Request_Empty_Spaces, TestFixture){
    std::u32string response =  bot.processMessage(U"   ");
    BOOST_CHECK(response == U"");
    Logger::log("response:",response);
}

BOOST_FIXTURE_TEST_CASE(test_get_Request_Wrong_Text, TestFixture){
    std::u32string response =  bot.processMessage(U"náhodný text");
    BOOST_CHECK(response == U"");
    Logger::log("response:",response);
}