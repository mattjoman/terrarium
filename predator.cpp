#include <iostream>
#include "predator.h"


Predator::Predator(int id_) : Animal{id_} {
	type = "predator";
}


void Predator::inc_hunger()
{
	hunger++;
}


void Predator::print() {
	std::cout << "PREDATOR" << std::endl;
}


Predator::~Predator() {};
