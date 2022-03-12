#include "prey.h"


Prey::Prey(int id_, std::vector<float> pos_) : Animal{id_, pos_}
{
	type = "prey";
}


void Prey::inc_hunger()
{
	//std::cout << "Prey don't get hungry" << std::endl;
}


void Prey::print()
{
	std::cout << "PREY" << std::endl;
}


Prey::~Prey() {};
