#pragma once
#include <string>
#include <iostream>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <boost/date_time/gregorian/gregorian.hpp>

template <typename _T>
void Log(std::ostream& str,_T obj){
    str << obj;
}
void Log(std::ostream& str,std::u32string obj);
void Log(std::ostream& str,std::u32string_view obj);
void Log(std::ostream& str,boost::gregorian::date obj);

class Logger{
public: 
    static std::filesystem::path Logpath; 
    Logger() = delete;
    static void init(std::filesystem::path path);
    template <typename _T>
    static void log(_T obj){
    #ifdef Debug
        Log(std::cout,obj);
        std::cout << "\n";
    #endif
    }

    template <typename _T>
    static void log(std::string message,_T obj){
    #ifdef Debug
        std::cout << message << " ";
        Log(std::cout,obj);
        std::cout << "\n";
    #endif
    }

    template <typename _T>
    static void error(_T obj){
    #ifdef Debug
        Log(std::cout,obj);
        std::cout << "\n";
    #endif
        std::fstream uidlFile(Logpath, std::fstream::in | std::fstream::out | std::fstream::app);
        Log(uidlFile,obj);
         uidlFile << "\n";
    }

    template <typename _T>
    static void error(std::string message,_T obj){
    #ifdef Debug
        std::cout << message << " ";
        Log(std::cout,obj);
        std::cout << "\n";
    #endif
        std::fstream uidlFile(Logpath, std::fstream::in | std::fstream::out | std::fstream::app);
        uidlFile << message << " ";
        Log(uidlFile,obj);
        uidlFile << "\n";
    }

};