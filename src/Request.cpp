#include "Request.h"
#include <algorithm>
namespace STIN_Bot
{
    KeySet::KeySet(std::vector<std::u32string> keySet):
        keySet(keySet)
    {
    }
    bool KeySet::contains(const std::u32string& key)
    {
        return std::any_of(keySet.begin(),keySet.end(),[&key](const std::u32string &s){
            return s == key;
        });
    }
    bool KeySet::contains(std::u32string_view key)
    {
        return std::any_of(keySet.begin(),keySet.end(),[&key](const std::u32string &s){
            return s == key;
        });
    }
} // namespace STIN_Bot
