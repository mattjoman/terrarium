#pragma once

#include "animal.h"

struct Predator : Animal {
	Predator(int id);
	void inc_hunger();
	void print();
	~Predator();
};
