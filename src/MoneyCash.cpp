#include "MoneyCash.h"
#include <fstream>
#include <Logger.h>
#include <WebReader.h>
const boost::gregorian::date fdate(boost::gregorian::from_simple_string("2022-4-17"));

MoneyCash::MoneyCash(std::filesystem::path path):
    path(path)
{
    if(read()){
        write();
    }
}


bool MoneyCash::read_string(const std::string& str){
    boost::json::error_code ec;
    boost::json::value js = boost::json::parse(str,ec);
    if(ec){
        Logger::log("Parsing error");
        return true;
    }
    try{
        boost::json::array& ja = js.as_array();
        for(auto obj : ja){
            if(obj.is_object()){
                boost::json::object& object = obj.as_object();
                contents.push_back(
                    std::pair<boost::gregorian::date,Money<>>(
                        boost::gregorian::from_simple_string(object["date"].as_string().c_str()),
                        Money(object["cents"].as_int64())
                    )
                );
            }
        }
    }
    catch(std::exception& e){
        Logger::log(e.what());
        return true;
    }
    return false;
}

std::string MoneyCash::write_string(){
    boost::json::array js;
    for(auto pair : contents){
        js.emplace_back( boost::json::object{ {"date",boost::gregorian::to_iso_extended_string(pair.first)},{"cents",pair.second.getCents()}});
    }
    boost::json::value jv(js);
    return boost::json::serialize(jv);
}



bool MoneyCash::read(){
    std::ifstream stream(path, std::ifstream::in);
    if(!stream.is_open()){
        Logger::log("File not found!!!");
        Logger::log(path);
        std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
        return true;
    }
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> utfConverter;
    std::string s((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    return(read_string(s));
}

bool MoneyCash::write(){
    std::ofstream stream(path, std::ifstream::in);
    if(stream.is_open()){
        stream << write_string();
        return true;
    }
    return false;
}
/**
 * @brief 
 * 
 * @param date 
 * @return Money<> for given date, or 0 if impossible to get
 */
Money<> MoneyCash::getCuseforDate(boost::gregorian::date date){
    std::string date_s =  boost::gregorian::to_iso_extended_string(date);
    std::string euroData = getEuro(date_s.substr(8,2)+"." +date_s.substr(5,2)+"."+date_s.substr(0,4));
    try{
        return Money<>::getFromString(extractEuro(euroData));
    }
    catch(std::invalid_argument& e){
        Logger::log("Could not read Money for date: ",date);
        return Money<>(0);
    }
}

bool MoneyCash::containsDate(boost::gregorian::date schearchedDate){
    return std::any_of(contents.begin(),contents.end(),[schearchedDate](std::pair<boost::gregorian::date,Money<>> p){
        return schearchedDate == p.first;
    });
}
bool MoneyCash::getCourseTillToday(){
    boost::gregorian::date lookUpDate = fdate;
    boost::posix_time::ptime timeLocal = boost::posix_time::second_clock::local_time();
    boost::gregorian::date today = timeLocal.date();
    while(lookUpDate < today){
        if(!containsDate(lookUpDate)){
            Logger::log("notContained",lookUpDate);
            Money<> m = getCuseforDate(lookUpDate);
            contents.push_back(std::pair<boost::gregorian::date,Money<>>(lookUpDate,m ) );
        }
        lookUpDate+= boost::gregorian::date_duration (1);
    }

    std::sort(contents.begin(),contents.end(),[](std::pair<boost::gregorian::date,Money<>> d1,std::pair<boost::gregorian::date,Money<>> d2){
        return(d1.first < d2.first);
    });
    return true;
}