#pragma once
#include <stdlib.h>
#include <string>
#include <vector>

struct Birth
{
	std::string type;
	std::vector<float> pos;

	Birth(std::string type, std::vector<float> pos);
	~Birth();
};

