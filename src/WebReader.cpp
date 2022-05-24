#include "WebReader.h"
#include <Logger.h>
#include <exception>

/*
date format = DD.MM.YYYY
*/
std::string WebReader::date_to_str(boost::gregorian::date date){
    std::string date_s =  boost::gregorian::to_iso_extended_string(date);
    
    return std::string(date_s.substr(8,2)+"." +date_s.substr(5,2)+"."+date_s.substr(0,4));
}

std::string WebReader::getCourse(boost::gregorian::date date) {
    
    std::string date_s =  date_to_str(date);
    
    boost::asio::ip::tcp::iostream stream;
    stream.expires_from_now(std::chrono::seconds(5));
    stream.connect("www.cnb.cz", "http");
    boost::system::error_code ec;
    stream.socket().remote_endpoint(ec);
    if (ec)
    {
        Logger::error("Unable to connect to:","www.cnb.cz");
        Logger::error("reason:",ec.message());
        return "";
    }
    stream    << "GET /cs/financni-trhy/devizovy-trh/kurzy-devizoveho-trhu/kurzy-devizoveho-trhu/denni_kurz.txt?date=" << date_s << " HTTP/1.1\r\n";
    stream    << "Host: www.cnb.cz\r\n";
    stream    << "Cache-Control: no-cache\r\n";
    // stream << "Content-Type: application/x-www-form-urlencoded\r\n\r\n";
    stream    << "Connection: close\r\n\r\n" << std::flush;
    std::ostringstream os;
    os << stream.rdbuf();
    return os.str();
}

std::string WebReader::extractCourse(const std::string &euroData, const std::string& money){
    if(euroData.size()==0){
        return "";
    }
    size_t euridx = euroData.find(money);
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

