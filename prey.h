#pragma once
#include <iostream>
#include "animal.h"
#include "includes.h"

struct Prey : Animal {
	Prey(int id);
	void print();
	~Prey();
};
