#include "Res.h"

namespace STIN_Bot
{
    Res::Res(std::vector<std::unique_ptr<Resource>> resorces){
        for(std::unique_ptr<Resource>& resource : resorces){
            res[resource->getName()] = std::move(resource);
        }
    }
    bool Res::contains(std::string name){
        return res.count(name)>0;
    }
    Resource* Res::operator[](const std::string&s){
        return res[s].get();
    }
} // namespace STIN_Bot
