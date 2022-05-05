#define BOOST_TEST_MODULE DummyTest
#include <boost/test/included/unit_test.hpp>

#include <resources/MoneyCash.h>
#include <Logger.h>

using namespace STIN_Bot;

class MoneyCash_mock : public MoneyCash{
public:
    MoneyCash_mock(std::filesystem::path path): 
        MoneyCash(path)
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
        getCourseTillToday();
        return contents;
    }

};


struct TestFixture{
    MoneyCash_mock moneyCash_mock;
    TestFixture():
        moneyCash_mock(std::filesystem::path("./build/Test/testMoneycash.json"))
    {
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
    {\"date\":\"2022-5-4\",\"cents\":2000}\
]";
    moneyCash_mock.setTestData(std::vector<std::pair<boost::gregorian::date,Money<>>> ());
    bool exec = moneyCash_mock.exposeRead_string(JSON_STR);
    std::vector<std::pair<boost::gregorian::date,Money<>>> contents =  moneyCash_mock.getContents();
    BOOST_CHECK_EQUAL(exec,false);
    BOOST_CHECK_EQUAL(contents.size(),4);
    BOOST_CHECK_EQUAL(moneyCash_mock.containsDate(boost::gregorian::from_simple_string("2022-5-1")),true);
    BOOST_CHECK_EQUAL(moneyCash_mock.containsDate(boost::gregorian::from_simple_string("2022-5-4")),true);
}

BOOST_FIXTURE_TEST_CASE( test_Get_Course_Till_Today, TestFixture )
{
    moneyCash_mock.setTestData(std::vector<std::pair<boost::gregorian::date,Money<>>>());
    moneyCash_mock.exposeGetCuseTillToday();
    Logger::log("read Contents Till Today");
    std::vector<std::pair<boost::gregorian::date,Money<>>> contents =  moneyCash_mock.getContents();
    
    BOOST_WARN(contents.size()>1);
    BOOST_WARN_EQUAL(moneyCash_mock.containsDate(fdate),true);
    Logger::log(contents.size());
}



BOOST_AUTO_TEST_CASE(test_Log_string){
    BOOST_CHECK(1 == 1);
}