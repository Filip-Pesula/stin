#define BOOST_TEST_MODULE TestHttoConnection
#include <boost/test/included/unit_test.hpp>

#include <HttpConnection.h>

using namespace STIN_Bot;
class http_connection_mock : public http_connection{
public:
    http_connection_mock(tcp::socket socket,const Resources &res): 
        http_connection(std::move(socket),res)
    {
    }
    void setreq(http::verb method,const char* fakeTarkget){
        request_.method(method);
        request_.target(fakeTarkget);
        request_.version(1);
    }
    http::response<http::dynamic_body> processReqTest(){
        process_request();
        return response_;
    }
};

BOOST_AUTO_TEST_CASE(test_macro_overview){

    std::filesystem::path p = ".";
    std::string resFile = "/testReadable.txt";
    p = p / "testRes" / resFile;
    Resources res({ {resFile, HtmlType::plain, p} });
    net::io_context ioc{ 1 };
    tcp::socket socket{ioc};
    std::shared_ptr<http_connection_mock> connection = std::make_shared<http_connection_mock>(std::move(socket),res);
    
    connection->setreq(http::verb::get,"/testReadable.txt");
    http::response<http::dynamic_body> resp = connection->processReqTest();
    BOOST_CHECK(resp.result()==http::status::ok);

    connection->setreq(http::verb::get,"/index.html");
    http::response<http::dynamic_body> resp2 = connection->processReqTest();
    BOOST_CHECK(resp2.result()==http::status::not_found);


    connection->setreq(http::verb::post,"/index.html");
    http::response<http::dynamic_body> resp3 = connection->processReqTest();
    BOOST_CHECK(resp3.result()==http::status::ok);

    connection->setreq(http::verb::head,"/index.html");
    http::response<http::dynamic_body> resp4 = connection->processReqTest();
    BOOST_CHECK(resp4.result()==http::status::bad_request);


}