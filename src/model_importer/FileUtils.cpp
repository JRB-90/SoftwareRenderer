#include "FileUtils.h"

using namespace softengine;

std::vector<std::string> FileUtils::explode(
    const std::string& s, 
    char c)
{
    std::string buff{ "" };
    std::vector<std::string> v;

    for (auto n : s)
    {
        if (n != c) buff += n; else
        {
            if (n == c && buff != "")
            {
                v.push_back(buff); buff = "";
            }
        }
    }
    if (buff != "")
    {
        v.push_back(buff);
    }

    return v;
}
