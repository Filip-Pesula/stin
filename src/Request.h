#pragma once
#include <vector>
#include <string>
namespace STIN_Bot{
    class KeySet{
        std::vector<std::u32string> keySet;
    public:
        KeySet(std::vector<std::u32string> keySet);
        bool contains(const std::u32string&);
        bool contains(std::u32string_view);
    };
    class Request{
    public:
        virtual std::vector<KeySet> getKeysets() const = 0;
        virtual std::u32string getResponse() const = 0;
    };
}