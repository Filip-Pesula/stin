#include "utils.h"
#include <iostream>
#include <sstream>
#include <boost/lexical_cast.hpp>
namespace STIN_Bot{
    std::time_t now()
    {
        return std::time(0);
    }
    std::string now_s()
    {
        time_t rawTimeNow = std::time(0);
        auto localeTimeNow = *std::localtime(&rawTimeNow);
        std::ostringstream oss;
        oss << std::put_time(&localeTimeNow, "%H:%M:%S");

        return oss.str();
    }
    std::string gen404(std::string adr){
        std::stringstream ss;
        ss << "<!DOCTYPE html>\n" 
        << "<html lang=\"en\">\n"
        << "<head>\n"
        << "\t<meta charset=\"UTF-8\">\n"
        << "\t<title>PAGE NOT FOUND</title>\n"
        << "</head>\n"
        << "<body>\n"
        << "\t<header>\n"
        << "\t404 Page: " << adr << " Not Found\n"
        << "\t</header>\n"
        << "</body>\n"
        << "</html>\n";
        std::string msg = ss.str();
        return msg;
    }
    boost::gregorian::date today(){
       boost::posix_time::ptime timeLocal = boost::posix_time::second_clock::local_time();
        return timeLocal.date(); 
    }
    
}