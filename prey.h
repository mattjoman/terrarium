#pragma once
#include <iostream>
#include "animal.h"
#include "includes.h"

struct Prey : Animal {
	Prey(int id, std::vector<float> pos);
	void inc_hunger();
	void print();
	~Prey();
};
