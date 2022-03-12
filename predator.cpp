#include <iostream>
#include "predator.h"


Predator::Predator(int id_, std::vector<float> pos_) : Animal{id_, pos_}
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
