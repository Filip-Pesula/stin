#pragma once
#include <filesystem>
#include <string>
#include <vector>
#include <ctime>
#include <utility>
#include <boost/json.hpp>
#include "Resoruce.h"
#include <Money.h>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace STIN_Bot{
    extern const boost::gregorian::date fdate;

    class MoneyCash : public Resource{
    public:
        static const std::string name;
    protected:
        std::filesystem::path path;
        std::vector<std::pair<boost::gregorian::date,Money<>>> contents; 
        bool read_string(const std::string& str);
        std::string write_string();
        Money<> getCuseforDate(boost::gregorian::date);
        bool getCourseTillToday();

    public:
        MoneyCash(std::filesystem::path path);
        
        std::string getName() override;

        bool read();

        bool write();

        bool containsDate(boost::gregorian::date);
        
        Money<> latest();

        std::vector<std::pair<boost::gregorian::date,Money<>>> history();


        Money<> get(boost::gregorian::date);
    };
}