#include "Utils.h"
#include "Matrix4.h"

#include <iostream>

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

void Utils::PrintMatrix(Matrix4 mat)
{
    std::printf("%.3f\t%.3f\t%.3f\t%.3f\n", mat.At(0, 0), mat.At(0, 1), mat.At(0, 2), mat.At(0, 3));
    std::printf("%.3f\t%.3f\t%.3f\t%.3f\n", mat.At(1, 0), mat.At(1, 1), mat.At(1, 2), mat.At(1, 3));
    std::printf("%.3f\t%.3f\t%.3f\t%.3f\n", mat.At(2, 0), mat.At(2, 1), mat.At(2, 2), mat.At(2, 3));
    std::printf("%.3f\t%.3f\t%.3f\t%.3f\n\n", mat.At(3, 0), mat.At(3, 1), mat.At(3, 2), mat.At(3, 3));
}
