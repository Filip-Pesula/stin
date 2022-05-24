#define BOOST_TEST_MODULE TestBot
#include <boost/test/included/unit_test.hpp>

#include <Bot.h>
#include <Logger.h>
#include <filesystem>
#include <resources/MoneyCash.h>
#include <cstdio>

#include <boost/date_time/gregorian/greg_duration.hpp>

using namespace STIN_Bot;

class MockController{
public:
    enum TestType{
        descend_below_10,
        descend_above_10,
        ascend,
        not_enough
    } testType = TestType::descend_below_10;
    MockController(MockController::TestType tt):
    testType(tt)
    {
    }
    void setTest(TestType _testType){
        testType = _testType;
    }
};

class WebReaderMock : public WebReader{
public:
    const MockController& mockController;
    WebReaderMock(MockController& mockController):
        mockController(mockController)
    {
    }
    std::string getCourse(boost::gregorian::date date) override {
        boost::posix_time::ptime timeLocal = boost::posix_time::second_clock::local_time();
        boost::gregorian::date today = timeLocal.date();
        switch (mockController.testType)
        {
        case MockController::TestType::descend_below_10:
            if(date == today){
                return "";
            }
            else if(date == (today - boost::gregorian::date_duration (1)) ){
                return "02.05.2022 #84\nEMU|euro|1|EUR|24,570";
            }
            else if(date == (today - boost::gregorian::date_duration (2)) ){
                return "02.05.2022 #84\nEMU|euro|1|EUR|24,670";
            }
            else if(date == today - boost::gregorian::date_duration (3) ){
                return "02.05.2022 #84\nEMU|euro|1|EUR|24,870";
            }
            else if(date == today - boost::gregorian::date_duration (4) ){
                return "02.05.2022 #84\nEMU|euro|1|EUR|24,970";
            }
            else if(date == today - boost::gregorian::date_duration (5) ){
                return "02.05.2022 #84\nEMU|euro|1|EUR|25,030";
            }
            break;
        case MockController::TestType::descend_above_10:
            if(date == today){
                return "";
            }
            else if(date == today - boost::gregorian::date_duration (1) ){
                return "02.05.2022 #84\nEMU|euro|1|EUR|21,570";
            }
            else if(date == today - boost::gregorian::date_duration (2) ){
                return "02.05.2022 #84\nEMU|euro|1|EUR|24,670";
            }
            else if(date == today - boost::gregorian::date_duration (3) ){
                return "02.05.2022 #84\nEMU|euro|1|EUR|26,870";
            }
            else if(date == today - boost::gregorian::date_duration (4) ){
                return "02.05.2022 #84\nEMU|euro|1|EUR|29,970";
            }
            else if(date == today - boost::gregorian::date_duration (5) ){
                return "02.05.2022 #84\nEMU|euro|1|EUR|32,030";
            }
            break;
        case MockController::TestType::not_enough:
            return "02.05.2022 #84\nEMU|euro|1|EUR|00,000";
        
        default:
            if(date == today){
                return "";
            }
            else if(date == today - boost::gregorian::date_duration (1) ){
                return "02.05.2022 #84\nEMU|euro|1|EUR|32,570";
            }
            else if(date == today - boost::gregorian::date_duration (2) ){
                return "02.05.2022 #84\nEMU|euro|1|EUR|28,670";
            }
            else if(date == today - boost::gregorian::date_duration (3) ){
                return "02.05.2022 #84\nEMU|euro|1|EUR|27,870";
            }
            else if(date == today - boost::gregorian::date_duration (4) ){
                return "02.05.2022 #84\nEMU|euro|1|EUR|26,970";
            }
            else if(date == today - boost::gregorian::date_duration (5) ){
                return "02.05.2022 #84\nEMU|euro|1|EUR|25,030";
            }
            break;
        }
        return "02.05.2022 #84\nEMU|euro|1|EUR|24,670";
    }
};


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

        requests.push_back(std::move(std::make_unique<GetEuroRecomandationRequestEN>()));
        requests.push_back(std::move(std::make_unique<GetEuroRecomandationRequestCZ>()));

        return requests;
    }
    MockController mockController; 
    WebReaderMock webReaderMock;
    Res res; 
    Bot bot;
    
    std::vector<std::unique_ptr<Resource>> getResources(){
        std::filesystem::path cash = "./build/Test"; 
        std::unique_ptr<STIN_Bot::MoneyCash> euroCash = std::unique_ptr<STIN_Bot::MoneyCash>(new MoneyCash( cash/"eurocas.json",webReaderMock));

        std::vector<std::unique_ptr<Resource>> resources;
        resources.push_back(std::move(euroCash));
        return resources;
    }

    TestFixture():
        mockController(MockController::TestType::ascend ),
        webReaderMock(mockController),
        res(std::move(getResources())),
        bot(std::move(makeRequests()),res)
    { 
    }
    TestFixture(MockController::TestType tt):
        mockController(tt),
        webReaderMock(mockController),
        res(std::move(getResources())),
        bot(std::move(makeRequests()),res)
    { 
    }
    ~TestFixture(){
        std::remove("./build/Test/eurocas.json");
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

BOOST_AUTO_TEST_CASE(test_get_Money_Dist_descend){
    boost::posix_time::ptime timeLocal = boost::posix_time::second_clock::local_time();
    boost::gregorian::date today = timeLocal.date();
    std::vector<std::pair<boost::gregorian::date,Money<>>> moneyh{
        { (today - boost::gregorian::date_duration (5)) , Money<>(2516)},
        { (today - boost::gregorian::date_duration (4)) , Money<>(2496)},
        { (today - boost::gregorian::date_duration (3)) , Money<>(2476)},
        { (today - boost::gregorian::date_duration (2)) , Money<>(2486)},
        { (today - boost::gregorian::date_duration (1)) , Money<>(2426)},
        { today , Money<>(0)},
    };
    float diff = getDifference(moneyh); 
    BOOST_CHECK_LT(diff, 0.f);
    BOOST_CHECK_GT(diff, -0.1f);
}
BOOST_AUTO_TEST_CASE(test_get_Money_Dist_descend_above_10){
    boost::posix_time::ptime timeLocal = boost::posix_time::second_clock::local_time();
    boost::gregorian::date today = timeLocal.date();
    std::vector<std::pair<boost::gregorian::date,Money<>>> moneyh{
        { (today - boost::gregorian::date_duration (5)) , Money<>(4216)},
        { (today - boost::gregorian::date_duration (4)) , Money<>(3596)},
        { (today - boost::gregorian::date_duration (3)) , Money<>(3076)},
        { (today - boost::gregorian::date_duration (2)) , Money<>(2486)},
        { (today - boost::gregorian::date_duration (1)) , Money<>(2026)},
        { today , Money<>(0)},
    };
    float diff = getDifference(moneyh); 
    BOOST_CHECK_LT(diff, -0.1f);
}
BOOST_AUTO_TEST_CASE(test_get_Money_Dist_ascend){
    boost::posix_time::ptime timeLocal = boost::posix_time::second_clock::local_time();
    boost::gregorian::date today = timeLocal.date();
    std::vector<std::pair<boost::gregorian::date,Money<>>> moneyh{
        { (today - boost::gregorian::date_duration (5)) , Money<>(2016)},
        { (today - boost::gregorian::date_duration (4)) , Money<>(2196)},
        { (today - boost::gregorian::date_duration (3)) , Money<>(2476)},
        { (today - boost::gregorian::date_duration (2)) , Money<>(3086)},
        { (today - boost::gregorian::date_duration (1)) , Money<>(4226)},
        { today , Money<>(0)},
    };
    float diff = getDifference(moneyh); 
    BOOST_CHECK_GT(diff, 0.0f);
}
BOOST_AUTO_TEST_CASE(test_get_Money_Dist_ascend_missing){
    boost::posix_time::ptime timeLocal = boost::posix_time::second_clock::local_time();
    boost::gregorian::date today = timeLocal.date();
    std::vector<std::pair<boost::gregorian::date,Money<>>> moneyh{
        { (today - boost::gregorian::date_duration (7)) , Money<>(2016)},
        { (today - boost::gregorian::date_duration (6)) , Money<>(2016)},
        { (today - boost::gregorian::date_duration (5)) , Money<>(2076)},
        { (today - boost::gregorian::date_duration (4)) , Money<>(2086)},
        { (today - boost::gregorian::date_duration (3)) , Money<>(2096)},
        { (today - boost::gregorian::date_duration (2)) , Money<>(0)},
        { (today - boost::gregorian::date_duration (1)) , Money<>(0)},
        { today , Money<>(0)},
    };
    float diff = getDifference(moneyh); 
    BOOST_CHECK_GT(diff, 0.0f);
}

BOOST_AUTO_TEST_CASE(test_get_Money_Dist_ascend_missing_middle){
    boost::posix_time::ptime timeLocal = boost::posix_time::second_clock::local_time();
    boost::gregorian::date today = timeLocal.date();
    std::vector<std::pair<boost::gregorian::date,Money<>>> moneyh{
        { (today - boost::gregorian::date_duration (7)) , Money<>(2016)},
        { (today - boost::gregorian::date_duration (6)) , Money<>(2016)},
        { (today - boost::gregorian::date_duration (5)) , Money<>(2076)},
        { (today - boost::gregorian::date_duration (4)) , Money<>(2086)},
        { (today - boost::gregorian::date_duration (3)) , Money<>(0)},
        { (today - boost::gregorian::date_duration (2)) , Money<>(2096)},
        { (today - boost::gregorian::date_duration (1)) , Money<>(0)},
        { today , Money<>(0)},
    };
    float diff = getDifference(moneyh); 
    BOOST_CHECK_GT(diff, 0.0f);
    BOOST_CHECK_LT(diff, 0.1f);
}

BOOST_AUTO_TEST_CASE(test_get_Money_Dist_ascend_zero_devision){
    boost::posix_time::ptime timeLocal = boost::posix_time::second_clock::local_time();
    boost::gregorian::date today = timeLocal.date();
    std::vector<std::pair<boost::gregorian::date,Money<>>> moneyh{
        { (today - boost::gregorian::date_duration (7)) , Money<>(0)},
        { (today - boost::gregorian::date_duration (6)) , Money<>(0)},
        { (today - boost::gregorian::date_duration (5)) , Money<>(0)},
        { (today - boost::gregorian::date_duration (4)) , Money<>(0)},
        { (today - boost::gregorian::date_duration (3)) , Money<>(0)},
        { (today - boost::gregorian::date_duration (1)) , Money<>(0)},
        { (today - boost::gregorian::date_duration (2)) , Money<>(2096)},
        { today , Money<>(0)},
    };
    float diff = getDifference(moneyh);
    BOOST_CHECK_GT(diff, -0.1f);
    BOOST_CHECK_LT(diff, 0.1f);
}

BOOST_AUTO_TEST_CASE(test_Get_Euro_Recomandation_below_10_Request_CZ){
    TestFixture tf(MockController::TestType::descend_below_10);
    std::u32string response =  tf.bot.processMessage(U"doporuč nákup eura");
    BOOST_CHECK(response.find(U"Dopuručuji nakoupit:") != std::u32string::npos);
    BOOST_CHECK(response.find(U"neklesá") != std::u32string::npos);
    Logger::log("response:",response);
}

BOOST_AUTO_TEST_CASE(test_Get_Euro_Recomandation_above_10_Request_CZ){
    TestFixture tf(MockController::TestType::descend_above_10);
    std::u32string response =  tf.bot.processMessage(U"doporuč nákup eura");
    BOOST_CHECK(response.find(U"Nedopuručuji nakoupit:") != std::u32string::npos);
    BOOST_CHECK(response.find(U"klesá") != std::u32string::npos);
    Logger::log("response:",response);
}

BOOST_AUTO_TEST_CASE(test_Get_Euro_Recomandation_ascend_Request_CZ){
    TestFixture tf(MockController::TestType::ascend);
    std::u32string response =  tf.bot.processMessage(U"doporuč nákup eura");
    BOOST_CHECK(response.find(U"Dopuručuji nakoupit:") != std::u32string::npos);
    BOOST_CHECK(response.find(U"stoupá") != std::u32string::npos);
    Logger::log("response:",response);
}


BOOST_AUTO_TEST_CASE(test_Get_Euro_Recomandation_below_10_Request_EN){
    TestFixture tf(MockController::TestType::descend_below_10);
    std::u32string response =  tf.bot.processMessage(U"recommend euro purchese");
    BOOST_CHECK(response.find(U"Recommending purchase:") != std::u32string::npos);
    BOOST_CHECK(response.find(U"not descending") != std::u32string::npos);
    Logger::log("response:",response);
}

BOOST_AUTO_TEST_CASE(test_Get_Euro_Recomandation_above_10_Request_EN){
    TestFixture tf(MockController::TestType::descend_above_10);
    std::u32string response =  tf.bot.processMessage(U"recommend euro purchese");
    BOOST_CHECK(response.find(U"Not Recommending purchase:") != std::u32string::npos);
    BOOST_CHECK(response.find(U"descending") != std::u32string::npos);
    Logger::log("response:",response);
}

BOOST_AUTO_TEST_CASE(test_Get_Euro_Recomandation_ascend_Request_EN){
    TestFixture tf(MockController::TestType::ascend);
    std::u32string response =  tf.bot.processMessage(U"recommend euro purchese");
    BOOST_CHECK(response.find(U"Recommending purchase:") != std::u32string::npos);
    BOOST_CHECK(response.find(U"ascending") != std::u32string::npos);
    Logger::log("response:",response);
}

