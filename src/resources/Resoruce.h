#pragma once
#include <string>
class Resource{
public:
    virtual std::string getName() = 0;
    Resource() = default;
    Resource(const Resource&) = delete;
    Resource& operator=(const Resource&) = delete;
};