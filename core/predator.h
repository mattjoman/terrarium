#pragma once

#include "animal.h"

class Predator : public Animal {
	public:
		Predator(int id, std::vector<float> pos, int min_death_age, int max_death_age);
		void inc_hunger();
		void print();
		~Predator();
};
