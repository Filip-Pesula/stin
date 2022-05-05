#pragma once
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
#include <HttpConnection.h>
#include <resources/Res.h>
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

namespace STIN_Bot {
	class HTTPCore{
    protected:
        tcp::socket& socket;
        tcp::acceptor& acceptor;
        Bot bot;
        Res res;
    public:
        void setup();
        HTTPCore(tcp::acceptor& acceptor, tcp::socket& socket);
    };
	void http_server(tcp::acceptor& acceptor, tcp::socket& socket,Res &res,Bot& bot);
}