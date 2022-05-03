#pragma once
#include <filesystem>
#include <string>
#include <vector>
#include <ctime>
#include <utility>
#include <boost/json.hpp>

#include <Money.h>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

extern const boost::gregorian::date fdate;

class MoneyCash{
protected:
    std::filesystem::path path;
    std::vector<std::pair<boost::gregorian::date,Money<>>> contents; 
    bool read_string(const std::string& str);
    std::string write_string();
    Money<> getCuseforDate(boost::gregorian::date);
    bool getCourseTillToday();

public:
    MoneyCash(std::filesystem::path path);
    
    bool read();

    bool write();

    bool containsDate(boost::gregorian::date);
    
    Money<> get(boost::gregorian::date);
};