#include <iostream>
#include "animal.h"
#include "basic_funcs.h"

Animal::Animal(int id_) : id{id_} {
	age = 0;
	preg_status = 0;
	pos = rand_vector(0, SPAWN_RADIUS);
	vel = rand_direction();
	hunger = 0;
}

void Animal::move() {
	pos[0] += vel[0];
	pos[1] += vel[1];
}

void Animal::print_pos() {
	std::cout << pos[0] << "," << pos[1] << std::endl;
}

void Animal::print() {
	std::cout << "ANIMAL" << std::endl;
}

Animal::~Animal() {}
