#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include <utils.h>
#include "HttpCore.h"
#include "utils.h"
#include <resources/Resources.h>
#include <resources/Res.h>
#include <resources/MoneyCash.h>
#include <Logger.h>
#include <filesystem>
#include <ReadArgs.h>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>



int main(int argc, char* argv[])
{
    try
    {
        net::ip::address address;
        unsigned short port;
        std::filesystem::path root;
        std::filesystem::path cash;
        // Check command line arguments.
        {
            std::string message; 
            auto PairList = GetArgsPairList(argc,argv);
            bool error = setUp(PairList,message,address,port,root,cash);
            if(error){
                std::cout << message;
                return EXIT_FAILURE;
            }
        }
        
        std::unique_ptr<STIN_Bot::Resources> htmlRes = std::make_unique<STIN_Bot::Resources>( 
            std::vector<STIN_Bot::ResourceData>{ 
                { std::string("/"), STIN_Bot::HtmlType::html, root/"ui"/"index.html" },
                { std::string("/BotClient.js"),STIN_Bot::HtmlType::js, root/ "ui" / "BotClient.js"},
                { std::string("/BotVisual.css"),STIN_Bot::HtmlType::css, root/ "ui" / "BotVisual.css"}
            }
        );
        WebReader webReader;
        std::unique_ptr<STIN_Bot::MoneyCash> euroCash = std::make_unique<STIN_Bot::MoneyCash>(cash/"eurocas.json",webReader);

        std::vector<std::unique_ptr<Resource>> resources;
        resources.push_back(std::move(htmlRes));
        resources.push_back(std::move(euroCash));
        STIN_Bot::Res res(std::move(resources));
        std::vector<std::unique_ptr<STIN_Bot::Request>> requests;
        requests.push_back(std::move(std::make_unique<STIN_Bot::GetNameRequestCZ>()));
        requests.push_back(std::move(std::make_unique<STIN_Bot::GetNameRequestEN>()));
        requests.push_back(std::move(std::make_unique<STIN_Bot::GetTimeRequestCZ>()));
        requests.push_back(std::move(std::make_unique<STIN_Bot::GetTimeRequestEN>()));
        requests.push_back(std::move(std::make_unique<STIN_Bot::GetEuroRequestCZ>()));
        requests.push_back(std::move(std::make_unique<STIN_Bot::GetEuroRequestEN>()));
        requests.push_back(std::move(std::make_unique<STIN_Bot::GetHelpRequestCZ>()));
        requests.push_back(std::move(std::make_unique<STIN_Bot::GetHelpRequestEN>()));
        requests.push_back(std::move(std::make_unique<STIN_Bot::GetEuroHystoryRequestEN>()));
        requests.push_back(std::move(std::make_unique<STIN_Bot::GetEuroHystoryRequestCZ>()));
        requests.push_back(std::move(std::make_unique<STIN_Bot::GetEuroRecomandationRequestEN>()));
        requests.push_back(std::move(std::make_unique<STIN_Bot::GetEuroRecomandationRequestCZ>()));
        STIN_Bot::Bot bot(std::move(requests),res);

        net::io_context ioc{ 1 };

        tcp::acceptor acceptor{ ioc, {address, port} };
        tcp::socket socket{ ioc };
        Logger::log("Server: START");
        STIN_Bot::http_server(acceptor, socket,res,bot);

        ioc.run();
    }
    catch (std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}