#pragma once
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <utility>
#include <cstdint>
#include <filesystem>
#include <ResourceData.h>


namespace STIN_Bot{

    enum class Files{
        index = 1,
        BotClient = 2,
        BotVisual = 3
    };


    class Resources{
        std::map<std::string,ResourceData> paths;
    public:
        std::map<std::string,std::u32string> files;
        bool exists(const std::string &name) const;
        Resources(std::vector<ResourceData> fileFetch);
    };
}