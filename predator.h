#pragma once

#include "animal.h"

struct Predator : Animal {
	Predator(int id);
	void print();
	~Predator();
};
