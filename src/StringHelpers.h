#pragma once
#include <string>

template <typename ...Args>
std::string stringWithFormat(const std::string& format, Args && ...args)
{
    auto size = std::snprintf(nullptr, 0, format.c_str(), std::forward<Args>(args)...);
    std::string output(size, '\0');
    std::sprintf(&output[0], format.c_str(), std::forward<Args>(args)...);
    return output;
}