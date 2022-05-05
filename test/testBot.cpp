#define BOOST_TEST_MODULE TestBot
#include <boost/test/included/unit_test.hpp>

#include <Bot.h>
#include <Logger.h>
#include <filesystem>
#include <resources/MoneyCash.h>

using namespace STIN_Bot;


struct TestFixture{
    std::vector<std::unique_ptr<Request>> makeRequests(){
        std::vector<std::unique_ptr<Request>> requests{
        };
        requests.push_back(std::move(std::make_unique<GetNameRequestEN>()));
        requests.push_back(std::move(std::make_unique<GetNameRequestCZ>()));
        requests.push_back(std::move(std::make_unique<GetTimeRequestEN>()));
        requests.push_back(std::move(std::make_unique<GetTimeRequestCZ>()));
        requests.push_back(std::move(std::make_unique<GetEuroRequestEN>()));
        requests.push_back(std::move(std::make_unique<GetEuroRequestCZ>()));
        requests.push_back(std::move(std::make_unique<GetHelpRequestEN>()));
        requests.push_back(std::move(std::make_unique<GetHelpRequestCZ>()));
        requests.push_back(std::move(std::make_unique<GetEuroHystoryRequestEN>()));
        requests.push_back(std::move(std::make_unique<GetEuroHystoryRequestCZ>()));
        return requests;
    }
    Res res; 
    Bot bot;

    
    std::vector<std::unique_ptr<Resource>> getResources(){
        std::filesystem::path cash = "./build/Test"; 
        std::unique_ptr<STIN_Bot::MoneyCash> euroCash = std::make_unique<STIN_Bot::MoneyCash>(cash/"eurocas.json");
        std::vector<std::unique_ptr<Resource>> resources;
        resources.push_back(std::move(euroCash));
        return resources;
    }

    TestFixture():
        res(std::move(getResources())),
        bot(std::move(makeRequests()),res)
    { 
    }
};


BOOST_FIXTURE_TEST_CASE(test_get_Request_Nominal_1, TestFixture){
    std::u32string response =  bot.processMessage(U"jak se jmenuješ");
    BOOST_CHECK(response == U"Jmenuji se ChatBot");
    Logger::log("response:",response);
}

BOOST_FIXTURE_TEST_CASE(test_get_Request_Nominal_2, TestFixture){
    std::u32string response =  bot.processMessage(U"what is your name");
    BOOST_CHECK(response == U"My name is Chatbot");
    Logger::log("response:",response);
}

BOOST_FIXTURE_TEST_CASE(test_get_Request_Nominal_3, TestFixture){
    std::u32string response =  bot.processMessage(U"jaký je čas");
    BOOST_CHECK(response.find(U"Je ") != std::u32string::npos);
    Logger::log("response:",response);
}

BOOST_FIXTURE_TEST_CASE(test_get_Request_Nominal_4, TestFixture){
    std::u32string response =  bot.processMessage(U"what time is it");
    BOOST_CHECK(response.find(U"It's") != std::u32string::npos);
    Logger::log("response:",response);
}

BOOST_FIXTURE_TEST_CASE(test_get_Request_Help_CZ, TestFixture){
    std::u32string response =  bot.processMessage(U"pomoc");
    BOOST_CHECK(response.find(U"umí") != std::u32string::npos);
    Logger::log("response:",response);
}

BOOST_FIXTURE_TEST_CASE(test_get_Request_Help_EN, TestFixture){
    std::u32string response =  bot.processMessage(U"help");
    BOOST_CHECK(response.find(U"Request can be:") != std::u32string::npos);
    Logger::log("response:",response);
}

BOOST_FIXTURE_TEST_CASE(test_get_Request_Euro_CZ, TestFixture){
    std::u32string response =  bot.processMessage(U"kolik stojí euro");
    BOOST_CHECK(response.find(U"Euro Stojí: ") != std::u32string::npos);
    Logger::log("response:",response);
}

BOOST_FIXTURE_TEST_CASE(test_get_Request_Euro_EN, TestFixture){
    std::u32string response =  bot.processMessage(U"how much euro costs");
    BOOST_CHECK(response.find(U"Euro costs:") != std::u32string::npos);
    Logger::log("response:",response);
}


BOOST_FIXTURE_TEST_CASE(test_get_Request_Empty, TestFixture){
    std::u32string response =  bot.processMessage(U"");
    BOOST_CHECK(response == U"Unknown command try: help/pomoc");
    Logger::log("response:",response);
}

BOOST_FIXTURE_TEST_CASE(test_get_Request_Empty_Spaces, TestFixture){
    std::u32string response =  bot.processMessage(U"   ");
    BOOST_CHECK(response == U"Unknown command try: help/pomoc");
    Logger::log("response:",response);
}

BOOST_FIXTURE_TEST_CASE(test_get_Request_Wrong_Text, TestFixture){
    std::u32string response =  bot.processMessage(U"náhodný text");
    BOOST_CHECK(response == U"Unknown command try: help/pomoc");
    Logger::log("response:",response);
}

BOOST_FIXTURE_TEST_CASE(test_get_Request_Not_Enough, TestFixture){
    std::u32string response =  bot.processMessage(U"what ");
    BOOST_CHECK(response == U"Unknown command try: help/pomoc");
    Logger::log("response:",response);
}

BOOST_FIXTURE_TEST_CASE(test_get_Request_EuroHystory_CZ, TestFixture){
    std::u32string response =  bot.processMessage(U"historie eura");
    BOOST_CHECK(response.find(U"Hytorie Eura:") != std::u32string::npos);
    Logger::log("response:",response);
}

BOOST_FIXTURE_TEST_CASE(test_get_Request_EuroHystory_EN, TestFixture){
    std::u32string response =  bot.processMessage(U"euro history");
    BOOST_CHECK(response.find(U"Euro history:") != std::u32string::npos);
    Logger::log("response:",response);
}
