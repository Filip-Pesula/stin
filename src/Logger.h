#pragma once
#include <string>
#include <iostream>

template <typename _T>
void Log(_T obj){
    std::cout << obj;
}
void Log(std::u32string obj);
void Log(std::u32string_view obj);

class Logger{
public: 
    static std::string DEF_LOG_FOLDER;

    Logger() = delete;
    static void init();
    template <typename _T>
    static void log(_T obj){
    #ifdef Debug
        Log(obj);
        std::cout << "\n";
    #endif
    }

    template <typename _T>
    static void log(std::string message,_T obj){
    #ifdef Debug
        std::cout << message << " ";
        Log(obj);
        std::cout << "\n";
    #endif
    }
};