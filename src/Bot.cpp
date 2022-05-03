#include "Bot.h"
#include <memory>
#include <algorithm>
#include <vector>
#include <Logger.h>
namespace STIN_Bot
{
    Bot::Bot(std::vector<std::unique_ptr<Request>> requests):
        requests(std::move(requests))
    {
    }
    std::u32string Bot::processMessage(const std::u32string &message){
        std::vector<size_t> indexes(requests.size());
        std::u32string_view message_sv{message.c_str()};
        std::fill(indexes.begin(),indexes.end(),0);
        size_t index = 0;
        std::u32string response;
        while(index < message_sv.size() && index != std::string::npos){
            size_t idx = message_sv.find_first_of(U" ,\n\r",index);

            Logger::log("index: ", index);
            Logger::log("idx: ", idx);
            Logger::log("idxr: ", ((idx!= std::u32string::npos)? idx : message_sv.size()-1));
            std::u32string_view word = message_sv.substr(index,((idx!= std::u32string::npos)? idx : message_sv.size()) - index);
            Logger::log("word: ", word);
            for(size_t i = 0; i < requests.size();i++){
                if(requests[i]->getKeysets()[indexes[i]].contains(word)){
                    indexes[i]++;
                    if(!(indexes[i]<requests[i]->getKeysets().size())){
                        return requests[i]->getResponse();
                    }
                }
            }
            index = message_sv.find_first_not_of(U" ,\n\r",idx);
        }
        return response;
    }
} // namespace STIN_Bot
