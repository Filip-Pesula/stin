#include "HttpConnection.h"
#include "utils.h"
#include <codecvt>
#include <locale>
#include <Logger.h>
namespace STIN_Bot{
    http_connection::http_connection(tcp::socket socket,const Resources &res): 
        socket_(std::move(socket)),
        res(res)
    {
    }
    void http_connection::start()
    {
        read_request();
        check_deadline();
    }
    void http_connection::read_request()
    {
        auto self = shared_from_this();

        http::async_read(
            socket_,
            buffer_,
            request_,
            [self](beast::error_code ec,
                std::size_t bytes_transferred)
            {
                boost::ignore_unused(bytes_transferred);
                if (!ec)
                    self->process_request();
            });
    }
    void http_connection::process_request()
    {
        response_.version(request_.version());
        response_.keep_alive(false);
        //Loggs target
        Logger::log(request_.target().to_string());
        
        switch (request_.method())
        {
        case http::verb::get:
            response_.result(http::status::ok);
            response_.set(http::field::server, "Beast");
            create_response();
            break;
        case http::verb::post:
            Logger::log("PostReques");
            response_.result(http::status::ok);
            response_.set(http::field::content_type, "text/plain");
            beast::ostream(response_.body()) << "Bot is Sleeping, come back next time";
            break;
        default:
            // We return responses indicating an error if
            // we do not recognize the request method.
            response_.result(http::status::bad_request);
            response_.set(http::field::content_type, "text/plain");
            beast::ostream(response_.body())
                << "Invalid request-method '"
                << std::string(request_.method_string())
                << "'";
            break;
        }

        write_response();
    }
    void http_connection::create_response()
    {
        if( res.exists(request_.target().to_string() )){
            std::u32string content = res.files.at(request_.target().to_string());
            std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> utfConverter;
            beast::ostream(response_.body()) << utfConverter.to_bytes(content);
        }
        else
        {
            response_.result(http::status::not_found);
            response_.set(http::field::content_type, "text/html");
            beast::ostream(response_.body()) << gen404(request_.target().to_string());
        }
    }
    void http_connection::write_response()
    {
        auto self = shared_from_this();

        response_.content_length(response_.body().size());

        http::async_write(
            socket_,
            response_,
            [self](beast::error_code ec, std::size_t)
            {
                self->socket_.shutdown(tcp::socket::shutdown_send, ec);
                self->deadline_.cancel();
            });
    }
    void http_connection::check_deadline()
    {
        auto self = shared_from_this();

        deadline_.async_wait(
            [self](beast::error_code ec)
            {
                if (!ec)
                {
                    // Close socket to cancel any outstanding operation.
                    self->socket_.close(ec);
                }
            });
    }
}