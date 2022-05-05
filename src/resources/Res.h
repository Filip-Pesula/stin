#pragma once
#include "Resoruce.h"
#include <map>
#include <memory>
#include <vector>
namespace STIN_Bot{
    class Res{
        std::map<std::string,std::unique_ptr<Resource>> res;
    public:
        Res(std::vector<std::unique_ptr<Resource>> resorces);
        bool contains(std::string);
        Resource* operator[](const std::string&s);
        Res(const Res&) = delete;
        Res& operator=(const Res&) = delete;
    };
}