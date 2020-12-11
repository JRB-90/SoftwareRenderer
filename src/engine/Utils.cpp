#include "Utils.h"

using namespace softengine;

std::vector<std::string> Utils::SplitString(
	const std::string& input, 
	char delimiter)
{
	std::vector<std::string> tokens;
    size_t pos_start = 0;
    size_t pos_end = 0;
    std::string token;

    while ((pos_end = input.find(delimiter, pos_start)) != std::string::npos)
    {
        token = input.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + 1;
        tokens.push_back(token);
    }

    tokens.push_back(input.substr(pos_start));

	return tokens;
}
