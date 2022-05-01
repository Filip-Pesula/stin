#pragma once
#include <chrono>
#include <string>
namespace STIN_Bot{
    std::size_t request_count();
    std::time_t now();
    std::string gen404(std::string adr);
}