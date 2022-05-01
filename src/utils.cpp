#include "utils.h"
#include <iostream>
#include <sstream>
namespace STIN_Bot{
    std::time_t now()
    {
        return std::time(0);
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
}