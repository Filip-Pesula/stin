#include "Logger.h"
#include <codecvt>
#include <locale>
std::string Logger::DEF_LOG_FOLDER = "/Log";
void Logger::init(){

}
void Log(std::u32string obj){
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> utfConverter;
    std::cout << utfConverter.to_bytes(obj);
}

void Log(std::u32string_view obj){
    std::u32string strO(obj);
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> utfConverter;
    std::cout << utfConverter.to_bytes(strO);
}
