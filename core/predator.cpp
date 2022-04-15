#include <iostream>
#include "predator.h"


Predator::Predator(int id_, std::vector<float> pos_, int min_death_age, int max_death_age) : Animal{id_, pos_, min_death_age, max_death_age}
{
	type = "predator";
}


void Predator::inc_hunger()
{
	hunger++;
}


void Predator::print()
{
	std::cout << "PREDATOR" << std::endl;
}


Predator::~Predator() {};
