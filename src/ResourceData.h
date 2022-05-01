#pragma once
#include <string>
#include <filesystem>
namespace STIN_Bot{
    enum class HtmlType{
        html,
        css,
        js,
        plain
    };
    class ResourceData{
    public:
        const std::string name;
        const HtmlType type;
        const std::filesystem::path path;
        static std::string getTypeTesxt(HtmlType type);
    };

}