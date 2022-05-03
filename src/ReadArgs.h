#pragma once
#include <vector>
#include <utility>
#include <string>
#include <filesystem>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>


static const std::filesystem::path defaultRoot = ".";

std::vector<std::pair<std::string,std::string>> 
GetArgsPairList(int argc, char** const argv);

bool
setUp(
    std::vector<std::pair<std::string,std::string>> argsList,
    std::string &message,
    boost::asio::ip::address &adress,
    unsigned short &port, 
    std::filesystem::path &root,
    std::filesystem::path &cash
);