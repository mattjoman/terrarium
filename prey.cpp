#include "prey.h"

Prey::Prey(int id_) : Animal{id_} {
	type = "prey";
}

void Prey::print() {
	std::cout << "PREY" << std::endl;
}

Prey::~Prey() {};
