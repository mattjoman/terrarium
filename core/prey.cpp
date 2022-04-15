#include "prey.h"


Prey::Prey(int id_, std::vector<float> pos_, int min_death_age, int max_death_age) : Animal{id_, pos_, min_death_age, max_death_age}
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
