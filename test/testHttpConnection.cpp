#define BOOST_TEST_MODULE TestHttoConnection
#include <boost/test/included/unit_test.hpp>

#include <HttpConnection.h>
#include <resources/Resources.h>

using namespace STIN_Bot;
class http_connection_mock : public http_connection{
public:
    http_connection_mock(tcp::socket socket,Res &res,Bot& bot): 
        http_connection(std::move(socket),res,bot)
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
    std::unique_ptr<Resource> httpRes = std::make_unique<Resources>(std::vector<ResourceData>{ {resFile, HtmlType::plain, p} });
    std::vector<std::unique_ptr<Resource>> resVec;
    resVec.push_back(std::move(httpRes));
    Res res(std::move(resVec));

    std::vector<std::unique_ptr<STIN_Bot::Request>> requests;
    requests.push_back(std::make_unique<GetNameRequestCZ>());
    requests.push_back(std::make_unique<GetNameRequestEN>());
    requests.push_back(std::make_unique<GetTimeRequestCZ>());
    requests.push_back(std::make_unique<GetTimeRequestEN>());
    Bot bot(std::move(requests),res);
    net::io_context ioc{ 1 };
    tcp::socket socket{ioc};
    std::shared_ptr<http_connection_mock> connection = std::make_shared<http_connection_mock>(std::move(socket),res,bot);
    
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