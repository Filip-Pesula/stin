#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <string>


class WebReader{
public:
    std::string date_to_str(boost::gregorian::date date);
#ifdef Debug
    virtual 
#endif
    std::string getCourse(boost::gregorian::date date);
    std::string extractCourse(const std::string &euroData,const std::string& money);
};