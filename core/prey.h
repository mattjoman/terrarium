#pragma once
#include <iostream>
#include "animal.h"
#include "../share/includes.h"

class Prey : public Animal {
	public:
		Prey(int id, std::vector<float> pos, int min_death_age, int max_death_age);
		void inc_hunger();
		void print();
		~Prey();
};
