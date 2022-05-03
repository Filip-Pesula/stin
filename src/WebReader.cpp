#include "WebReader.h"
#include <Logger.h>
#include <exception>
/*
date format = DD.MM.YYYY
*/
std::string getEuro(std::string const& date) {
    boost::asio::ip::tcp::iostream stream;
    stream.expires_from_now(std::chrono::seconds(5));
    stream.connect("www.cnb.cz", "http");
    boost::system::error_code ec;
    stream.socket().remote_endpoint(ec);
    if (ec)
    {
        Logger::log("Unable to connect to:","www.cnb.cz");
        return "";
    }
    stream    << "GET /cs/financni-trhy/devizovy-trh/kurzy-devizoveho-trhu/kurzy-devizoveho-trhu/denni_kurz.txt?date=" << date << " HTTP/1.1\r\n";
    stream    << "Host: www.cnb.cz\r\n";
    stream    << "Cache-Control: no-cache\r\n";
    // stream << "Content-Type: application/x-www-form-urlencoded\r\n\r\n";
    stream    << "Connection: close\r\n\r\n" << std::flush;
    std::ostringstream os;
    os << stream.rdbuf();
    return os.str();
}

std::string extractEuro(const std::string &euroData){
    if(euroData.size()==0){
        return "";
    }
    size_t euridx = euroData.find("EUR");
    if(euridx==std::string::npos){
        return "";
    }
    size_t euridxEnd = euroData.find_first_not_of("0123456789,",euridx+4);
    if(euridxEnd==std::string::npos){
        euridxEnd=euroData.size();
    }
    std::string money_str = euroData.substr(euridx+4,euridxEnd-euridx-4);
    return money_str;
}