#define BOOST_TEST_MODULE DummyTest

#include <gmock/gmock.h>
#include <boost/test/included/unit_test.hpp>

#include <resources/MoneyCash.h>
#include <Logger.h>
#include <cstdio>

using namespace STIN_Bot;
using namespace testing;

class WebReaderMock : public WebReader{
public:
    std::string getCourse(boost::gregorian::date date)override{
        return date_to_str(date) +
R"( #84
Indie|rupie|100|INR|30,647
Indonesie|rupie|1000|IDR|1,617
Island|koruna|100|ISK|17,981
Izrael|nový šekel|1|ILS|6,993
Japonsko|jen|100|JPY|18,057
Dánsko|koruna|1|DKK|3,316
EMU|euro|1|EUR|24,670
)";
    };
    
};

class MoneyCash_mock : public MoneyCash{
public:
    MoneyCash_mock(std::filesystem::path path,WebReaderMock& wrm): 
        MoneyCash(path, wrm)
    {
    }
    void setTestPath(std::filesystem::path path){
        this->contents = contents;
    }
    void setTestData(std::vector<std::pair<boost::gregorian::date,Money<>>> contents ){
        this->contents = contents;
    }
    bool exposeRead_string(const std::string& str){
        return read_string(str);
    }
    std::string exposeWrite_string(){
        return write_string();
    }
    std::vector<std::pair<boost::gregorian::date,Money<>>> getContents(){
        return contents;
    }
    Money<> exposeGetCuseforDate(boost::gregorian::date date){
        return getCuseforDate(date);
    }
    std::vector<std::pair<boost::gregorian::date,Money<>>> exposeGetCuseTillToday(){
        MoneyCash::getCourseTillToday();
        return contents;
    }

};


struct TestFixture{
    WebReaderMock wrm;
    MoneyCash_mock moneyCash_mock;
    TestFixture():
        moneyCash_mock(std::filesystem::path("./build/Test/testMoneycash.json"),wrm)
    {
        Logger::init(std::filesystem::path{"."}/"build"/"Test"/"log.txt");
    }
    ~TestFixture(){
        std::remove("./build/Test/testMoneycash.json");
        std::remove("./build/Test/log.txt");
    }
};

BOOST_FIXTURE_TEST_CASE( test_ReadJson_Nominal, TestFixture )
{
    std::string JSON_STR = 
"[\
    {\"date\":\"2022-5-1\",\"cents\":2014},\
    {\"date\":\"2022-5-2\",\"cents\":2017},\
    {\"date\":\"2022-5-3\",\"cents\":2018},\
    {\"date\":\"2022-5-4\",\"cents\":2000}\
]";
    moneyCash_mock.setTestData(std::vector<std::pair<boost::gregorian::date,Money<>>> ());
    bool exec = moneyCash_mock.exposeRead_string(JSON_STR);
    std::vector<std::pair<boost::gregorian::date,Money<>>> contents =  moneyCash_mock.getContents();
    BOOST_CHECK_EQUAL(exec,false);
    BOOST_CHECK_EQUAL(contents.size(),4);
    BOOST_CHECK_EQUAL(contents[0].first,boost::gregorian::from_simple_string("2022-5-1"));
    BOOST_CHECK_EQUAL(contents[0].second.getCents(),2014);
    
    BOOST_CHECK_EQUAL(contents[3].first,boost::gregorian::from_simple_string("2022-5-4"));
    BOOST_CHECK_EQUAL(contents[3].second.getCents(),2000);
}

BOOST_FIXTURE_TEST_CASE( test_ReadJson_Nominal_Read_WRite, TestFixture )
{
    std::string JSON_STR = 
"[\
{\"date\":\"2022-05-01\",\"cents\":2014},\
{\"date\":\"2022-05-02\",\"cents\":2017},\
{\"date\":\"2022-05-03\",\"cents\":2018},\
{\"date\":\"2022-05-04\",\"cents\":2000}\
]";
    moneyCash_mock.setTestData(std::vector<std::pair<boost::gregorian::date,Money<>>> ());
    bool exec = moneyCash_mock.exposeRead_string(JSON_STR);
    std::vector<std::pair<boost::gregorian::date,Money<>>> contents =  moneyCash_mock.getContents();
    std::string write = moneyCash_mock.exposeWrite_string();

    BOOST_CHECK_EQUAL(exec,false);
    BOOST_CHECK_EQUAL(JSON_STR,write);
}

BOOST_FIXTURE_TEST_CASE( test_ReadJson_SyntaxError, TestFixture )
{
    std::string JSON_STR = 
"[\
{\"date\":\"2022-05-01\",\"cents\":2014},\
\"date\":\"2022-05-02\",\"cents\":2017},\
{\"date\":\"2022-05-03\",\"cents\":2018},\
{\"date\":\"2022-05-04\",\"cents\":2000}\
]";
    moneyCash_mock.setTestData(std::vector<std::pair<boost::gregorian::date,Money<>>> ());
    bool exec = moneyCash_mock.exposeRead_string(JSON_STR);
    std::vector<std::pair<boost::gregorian::date,Money<>>> contents =  moneyCash_mock.getContents();
    BOOST_CHECK_EQUAL(exec,true);
    BOOST_CHECK_EQUAL(contents.size(),0);
}

BOOST_FIXTURE_TEST_CASE( test_ReadJson_NotArray, TestFixture )
{
    std::string JSON_STR = 
"\
{\"date\":\"2022-05-01\",\"cents\":2014}\
";
    moneyCash_mock.setTestData(std::vector<std::pair<boost::gregorian::date,Money<>>> ());
    bool exec = moneyCash_mock.exposeRead_string(JSON_STR);
    std::vector<std::pair<boost::gregorian::date,Money<>>> contents =  moneyCash_mock.getContents();
    BOOST_CHECK_EQUAL(exec,true);
    BOOST_CHECK_EQUAL(contents.size(),0);
}

BOOST_FIXTURE_TEST_CASE( test_GetCourse_For_Date, TestFixture )
{
    try{
        Money<> exec = moneyCash_mock.exposeGetCuseforDate(boost::gregorian::from_simple_string("2022-3-5"));
        BOOST_WARN_EQUAL(exec.getCents(),2466);
    }
    catch(std::exception& e){
        std::cout << e.what()<<std::endl;
    }
}

BOOST_FIXTURE_TEST_CASE( test_Contains, TestFixture )
{
    std::string JSON_STR = 
"[\
    {\"date\":\"2022-5-1\",\"cents\":2014},\
    {\"date\":\"2022-5-2\",\"cents\":2017},\
    {\"date\":\"2022-5-3\",\"cents\":2018},\
    {\"date\":\"2022-5-4\",\"cents\":2000},\
    {\"date\":\"2022-5-5\",\"cents\":0}\
]";
    moneyCash_mock.setTestData(std::vector<std::pair<boost::gregorian::date,Money<>>> ());
    bool exec = moneyCash_mock.exposeRead_string(JSON_STR);
    std::vector<std::pair<boost::gregorian::date,Money<>>> contents =  moneyCash_mock.getContents();
    BOOST_CHECK_EQUAL(exec,false);
    BOOST_CHECK_EQUAL(contents.size(),5);
    BOOST_CHECK_EQUAL(moneyCash_mock.containsDate(boost::gregorian::from_simple_string("2022-5-1")),true);
    BOOST_CHECK_EQUAL(moneyCash_mock.containsDate(boost::gregorian::from_simple_string("2022-5-4")),true);
    BOOST_CHECK_EQUAL(moneyCash_mock.containsDate(boost::gregorian::from_simple_string("2022-5-5")),true);
}

BOOST_FIXTURE_TEST_CASE( test_Get_Course_Till_Today, TestFixture )
{
    moneyCash_mock.setTestData(std::vector<std::pair<boost::gregorian::date,Money<>>>());
    moneyCash_mock.exposeGetCuseTillToday();
    Logger::log("read Contents Till Today");
    std::vector<std::pair<boost::gregorian::date,Money<>>> contents =  moneyCash_mock.getContents();
    
    BOOST_CHECK(contents.size()>1);
    BOOST_CHECK_EQUAL(moneyCash_mock.containsDate(fdate),true);
    BOOST_CHECK_EQUAL(contents[0].second.getCents(),2467);
    Logger::log(contents.size());
    Logger::log(contents[0].first);
    Logger::log(contents[0].second.to_string(std::string(",")));

}

BOOST_AUTO_TEST_CASE(test_Log_string){
    BOOST_CHECK(1 == 1);
}
