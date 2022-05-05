#include "ResourceData.h"

namespace STIN_Bot{
    std::string ResourceData::getTypeTesxt(HtmlType type)
    {
        switch (type)
        {
        case HtmlType::html:
            return "text/html";
            break;
        case HtmlType::css:
            return "text/css";
            break;
        case HtmlType::js:
            return "text/javascript";
            break;
        
        default:
            return "text/plain";
            break;
        }
    }
}