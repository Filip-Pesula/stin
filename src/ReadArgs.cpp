#include "ReadArgs.h"
#include <boost/lexical_cast.hpp>
#include <Logger.h>
std::vector<std::pair<std::string,std::string>> 
GetArgsPairList(int argc, char** const argv) {
    std::vector<std::pair<std::string,std::string>> pairList;
    if(argc>1){
        for (int i = 1; i < argc; i++)
        {
            if(argv[i][0] == '-'){
                pairList.push_back({std::string(argv[i]),std::string()});
            }
            else{
                if(!pairList.empty()){
                    pairList.back().second = std::string(argv[i]);
                }
            }
        }
        
    }
    return pairList;
}
bool
setUp(
    std::vector<std::pair<std::string,std::string>> argsList,
    std::string &message,
    boost::asio::ip::address &adress,
    unsigned short &port, 
    std::filesystem::path &root
){
    adress = boost::asio::ip::make_address("0.0.0.0");
    port = 80; 
    root = ".";
    for(auto argPair : argsList){
        if(argPair.first == "-adr"){
            if(argPair.second == ""){
                message = "missing ip adress after -adr";
                return true;
            }
            boost::system::error_code ec;
            adress = boost::asio::ip::make_address(argPair.second,ec);
            if(ec){
                message = "given ip adress after -adr is invalid:\n" + ec.message();
                return true;
            }
        }
        else if(argPair.first == "-port"){
            if(argPair.second == ""){
                message = "missing port after -port";
                return true;
            }
            try{
                port = boost::lexical_cast<unsigned short>(argPair.second);
            }
            catch (const boost::bad_lexical_cast &e)
            {
                message = "given port after -port is invalid:\n" + std::string(e.what());
                return true;
            }
        }
        else if(argPair.first == "-root"){
            if(argPair.second == ""){
                message = "missing directory after -root";
                return true;
            }
            std::filesystem::path validate = argPair.second;
            if(!std::filesystem::exists(validate)){
                message = "given direcory after -root is invalid:\n'" + validate.string() + "' Doesn't exist";
                return true;
            }
            else if(!std::filesystem::is_directory(validate)){
                message = "given direcory after -root is invalid:\nIs not a directory";
                return true;
            }
            root = validate;
        }
        else if(argPair.first == "-h"){
            message = 
"Usage\n\
\tChatBot [options]\n\
Options\n\
-adr <ip_adress>     = Specifies serverAdress IPV4 '0.0.0.0' | IPV6 '0::0'\n\
-port <port>         = Specifies listening port\n\
-root <root_folder>  = Specifies root directory to reference when looking for files\n\
";
            return true;
        }
    }
    return false;
}