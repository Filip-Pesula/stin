#include "HttpCore.h"
#include <Logger.h>
namespace STIN_Bot {
    
    void http_server(tcp::acceptor& acceptor, tcp::socket& socket,Res &res,Bot& bot)
    {
        acceptor.async_accept(socket,
        [&](beast::error_code ec)
        {
            if(!ec){
                Logger::log("Connection: OPEN");
                std::make_shared<http_connection>(std::move(socket),res,bot)->start();
            }
            Logger::log("Connection: CLOSED");
            http_server(acceptor, socket, res, bot);
        });
    }
}
