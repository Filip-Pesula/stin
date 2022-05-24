#include "Logger.h"
#include <codecvt>
#include <locale>
std::filesystem::path Logger::Logpath = std::filesystem::path{"."} / "Log"/"log.txt";
void Logger::init(std::filesystem::path path){
    Logpath = path;
}
void Log(std::ostream& str,std::u32string obj){
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> utfConverter;
    str << utfConverter.to_bytes(obj);
}

void Log(std::ostream& str,std::u32string_view obj){
    std::u32string strO(obj);
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> utfConverter;
    str << utfConverter.to_bytes(strO);
}
void Log(std::ostream& str,boost::gregorian::date obj){
    str << boost::gregorian::to_iso_extended_string(obj);
}
