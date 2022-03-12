#pragma once

#include "animal.h"

struct Predator : Animal {
	Predator(int id, std::vector<float> pos);
	void inc_hunger();
	void print();
	~Predator();
};
