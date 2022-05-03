#define BOOST_TEST_MODULE TestReadArgs
#include <boost/test/included/unit_test.hpp>

#include <ReadArgs.h>

BOOST_AUTO_TEST_CASE(test_Read_Nominal){
    char* args[] = {(char*)"this",(char*)"-adr",(char*)"0.0.0.0"};
    auto list = GetArgsPairList(3,args);
    BOOST_CHECK_EQUAL(list[0].first , "-adr");
    BOOST_CHECK_EQUAL(list[0].second , "0.0.0.0");
}

BOOST_AUTO_TEST_CASE(test_Read_Single){
    char* args[] = {(char*)"this",(char*)"-h"};
    auto list = GetArgsPairList(2,args);
    BOOST_CHECK_EQUAL(list[0].first , "-h");
    BOOST_CHECK_EQUAL(list[0].second , "");
}

BOOST_AUTO_TEST_CASE(test_Setup_Nominal){
    char* args[] = {(char*)"this",(char*)"-adr",(char*)"0::0", (char*)"-port",(char*)"60",(char*)"-root",(char*)".",(char*)"-cash",(char*)"."};
    auto list = GetArgsPairList(9,args);
    boost::asio::ip::address adr;
    unsigned short port;
    std::filesystem::path root;
    std::filesystem::path cash;
    std::string message;
    bool error = setUp(list,message,adr,port,root,cash);
    BOOST_CHECK_EQUAL(error , false);
    BOOST_CHECK_EQUAL(message , std::string());
    BOOST_CHECK_EQUAL(adr.to_string() , "::");
    BOOST_CHECK_EQUAL(port , 60);
    BOOST_CHECK_EQUAL(root , std::filesystem::path("."));
    BOOST_CHECK_EQUAL(cash , std::filesystem::path("."));
}

boost::asio::ip::address adr;
unsigned short port;
std::filesystem::path root;
std::filesystem::path cash;
std::string message;

void checkIsDefault(){
    BOOST_CHECK_EQUAL(adr.to_string() , "0.0.0.0");
    BOOST_CHECK_EQUAL(port , 80);
    BOOST_CHECK_EQUAL(root , std::filesystem::path("."));
}

BOOST_AUTO_TEST_CASE(test_Help){
    char* args[] = {(char*)"this",(char*)"-h"};
    auto list = GetArgsPairList(2,args);
    bool error = setUp(list,message,adr,port,root,cash);
    BOOST_CHECK_EQUAL(error , true);
    BOOST_CHECK_GT(message.size() , 1);
    BOOST_CHECK(message.find("Options") != std::string::npos);
    BOOST_CHECK(message.find("[options]") != std::string::npos);
    BOOST_CHECK(message.find("-adr") != std::string::npos);
    BOOST_CHECK(message.find("-port") != std::string::npos);
    BOOST_CHECK(message.find("-root") != std::string::npos);
    BOOST_CHECK(message.find("-cash") != std::string::npos);
    checkIsDefault();
}

BOOST_AUTO_TEST_CASE(test_Missing_adres){
    char* args[] = {(char*)"this",(char*)"-adr"};
    auto list = GetArgsPairList(2,args);
    bool error = setUp(list,message,adr,port,root,cash);
    BOOST_CHECK_EQUAL(error , true);
    BOOST_CHECK_GT(message.size() , 1);
    BOOST_CHECK(message.find("missing ip adress after -adr") != std::string::npos);
    checkIsDefault();
}

BOOST_AUTO_TEST_CASE(test_Invalid_adres){
    char* args[] = {(char*)"this",(char*)"-adr",(char*)"0.0.0.256"};
    auto list = GetArgsPairList(3,args);
    bool error = setUp(list,message,adr,port,root,cash);
    BOOST_CHECK_EQUAL(error , true);
    BOOST_CHECK_GT(message.size() , 1);
    BOOST_CHECK(message.find("-adr is invalid:") != std::string::npos);
    checkIsDefault();
}

BOOST_AUTO_TEST_CASE(test_Missing_port){
    char* args[] = {(char*)"this",(char*)"-port"};
    auto list = GetArgsPairList(2,args);
    bool error = setUp(list,message,adr,port,root,cash);
    BOOST_CHECK_EQUAL(error , true);
    BOOST_CHECK_GT(message.size() , 1);
    BOOST_CHECK(message.find("missing port after -port") != std::string::npos);
    checkIsDefault();
}

BOOST_AUTO_TEST_CASE(test_Invalid_port){
    char* args[] = {(char*)"this",(char*)"-port",(char*)"a"};
    auto list = GetArgsPairList(3,args);
    bool error = setUp(list,message,adr,port,root,cash);
    BOOST_CHECK_EQUAL(error , true);
    BOOST_CHECK_GT(message.size() , 1);
    BOOST_CHECK(message.find("-port is invalid:") != std::string::npos);
    checkIsDefault();
}

BOOST_AUTO_TEST_CASE(test_Missing_Root){
    char* args[] = {(char*)"this",(char*)"-root"};
    auto list = GetArgsPairList(2,args);
    bool error = setUp(list,message,adr,port,root,cash);
    BOOST_CHECK_EQUAL(error , true);
    BOOST_CHECK_GT(message.size() , 1);
    BOOST_CHECK(message.find("missing directory after -root") != std::string::npos);
    checkIsDefault();
}
BOOST_AUTO_TEST_CASE(test_Invalid_Root){
    char* args[] = {(char*)"this",(char*)"-root",(char*)"invalidRoot"};
    auto list = GetArgsPairList(3,args);
    bool error = setUp(list,message,adr,port,root,cash);
    BOOST_CHECK_EQUAL(error , true);
    BOOST_CHECK_GT(message.size() , 1);
    BOOST_CHECK_MESSAGE(
        message.find("-root is invalid:") != std::string::npos && 
        message.find("Doesn't exist") != std::string::npos,
        message);
    checkIsDefault();
}

BOOST_AUTO_TEST_CASE(test_Invalid_Root_File){
    char* args[] = {(char*)"this",(char*)"-root",(char*)"./testRes/testReadable.txt"};
    auto list = GetArgsPairList(3,args);
    bool error = setUp(list,message,adr,port,root,cash);
    BOOST_CHECK_EQUAL(error , true);
    BOOST_CHECK_GT(message.size() , 1);
    BOOST_CHECK_MESSAGE(message.find("Is not a directory")!= std::string::npos,message);
    checkIsDefault();
}


BOOST_AUTO_TEST_CASE(test_Missing_Cash){
    char* args[] = {(char*)"this",(char*)"-cash"};
    auto list = GetArgsPairList(2,args);
    bool error = setUp(list,message,adr,port,root,cash);
    BOOST_CHECK_EQUAL(error , true);
    BOOST_CHECK_GT(message.size() , 1);
    BOOST_CHECK(message.find("missing directory after -cash") != std::string::npos);
    checkIsDefault();
}
BOOST_AUTO_TEST_CASE(test_Invalid_Cash){
    char* args[] = {(char*)"this",(char*)"-cash",(char*)"invalidRoot"};
    auto list = GetArgsPairList(3,args);
    bool error = setUp(list,message,adr,port,root,cash);
    BOOST_CHECK_EQUAL(error , true);
    BOOST_CHECK_GT(message.size() , 1);
    BOOST_CHECK_MESSAGE(
        message.find("-cash is invalid:") != std::string::npos && 
        message.find("Doesn't exist") != std::string::npos,
        message);
    checkIsDefault();
}
BOOST_AUTO_TEST_CASE(test_Invalid_Cash_File){
    char* args[] = {(char*)"this",(char*)"-cash",(char*)"./testRes/testReadable.txt"};
    auto list = GetArgsPairList(3,args);
    bool error = setUp(list,message,adr,port,root,cash);
    BOOST_CHECK_EQUAL(error , true);
    BOOST_CHECK_GT(message.size() , 1);
    BOOST_CHECK_MESSAGE(message.find("Is not a directory")!= std::string::npos,message);
    checkIsDefault();
}


