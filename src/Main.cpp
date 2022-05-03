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
#include <Resources.h>
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
        
        STIN_Bot::Resources res( 
            { 
                { std::string("/"), STIN_Bot::HtmlType::html, root/"ui"/"index.html" },
                { std::string("/BotClient.js"),STIN_Bot::HtmlType::js, root/ "ui" / "BotClient.js"},
                { std::string("/BotVisual.css"),STIN_Bot::HtmlType::css, root/ "ui" / "BotVisual.css"}
            }
        );

        net::io_context ioc{ 1 };

        tcp::acceptor acceptor{ ioc, {address, port} };
        tcp::socket socket{ ioc };
        Logger::log("Server: START");
        STIN_Bot::http_server(acceptor, socket,res);

        ioc.run();
    }
    catch (std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}