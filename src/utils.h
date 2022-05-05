#pragma once
#include <chrono>
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace STIN_Bot{
    std::size_t request_count();
    std::time_t now();
    std::string now_s();
    std::string gen404(std::string adr);
    boost::gregorian::date today();
}