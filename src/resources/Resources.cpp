#include "Resources.h"
#include <fstream>
#include <codecvt>
#include <locale>
#include <Logger.h>
#include <filesystem>
namespace STIN_Bot{
    const std::string Resources::name = "HtmlResource";
    Resources::Resources(std::vector<ResourceData> fileFetch)
    {
        Logger::log(fileFetch.size());
        for(ResourceData file: fileFetch){
            std::ifstream stream(file.path, std::ifstream::in);
            if(!stream.is_open()){
                Logger::log("File not found!!!");
                Logger::log(file.path);
                std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
            }
            std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> utfConverter;
            std::string s((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

            std::u32string content = utfConverter.from_bytes(s);
            files[file.name] = std::move(content);
        }
    }
    bool Resources::exists(const std::string &name) const{
        return files.contains(name);
    }
    std::string Resources::getName(){
        return Resources::name;
    }
}