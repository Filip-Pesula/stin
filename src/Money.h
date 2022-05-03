#pragma once
#include <string>
#include <StringHelpers.h>
template<unsigned int Conv = 100>
class Money{
    unsigned int cents;
public:
    Money(unsigned int cents): cents(cents)
    {
    }
    Money(unsigned int unit,unsigned int cents): cents(cents+unit*Conv)
    {
    }
    int getCents(){
        return cents;
    }
    template<typename char_t>
    std::basic_string<char_t> to_string(std::basic_string<char_t> decimal){
        std::string u_char_s (std::to_string(cents/Conv));
        std::string c_char_s (stringWithFormat("%02d",cents%Conv));
        //std::string c_char_s (std::format("%02d",cents%Conv));
        std::basic_string<char_t> unit(u_char_s.begin(),u_char_s.end());
        std::basic_string<char_t> cents(c_char_s.begin(),c_char_s.end());
        return unit + decimal + cents;
    }
    template<typename char_t>
    std::basic_string<char_t> prefString(std::basic_string<char_t> decimal,std::basic_string<char_t> prefix){
        return prefix + this->to_string(decimal);
    }
    /**
     * @brief Get the From String object
     * 
     * @param m string in format uu,ddd (15,245)
     * @return Money 
     * @throw invalid_argument if m does not apply specified format or could not parse to numbers
     */
    static Money getFromString(const std::string& m){
        if(m.size()!=6){
            throw std::invalid_argument("incorrect money format");
        }
        if(m[2]!=','){
            throw std::invalid_argument("incorrect money format");
        }
        if(m.substr(0,2).find_first_not_of("0123456789")!=std::string::npos ||
           m.substr(3).find_first_not_of("0123456789")!=std::string::npos){
            throw std::invalid_argument("incorrect money format");
        }
        try{
            int unit = std::stoi( m.substr(0,2) );
            int cents = std::stoi( m.substr(3) )/10;
            return Money<>(unit,cents);
        }
        catch(std::exception& e){
            throw std::invalid_argument("incorrect money format");
        }
    }
};