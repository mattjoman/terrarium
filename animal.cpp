#include <iostream>
#include "animal.h"
#include "basic_funcs.h"
#include "config.h"


Animal::Animal(int id_, std::vector<float> pos_) : id{id_}, pos{pos_}
{
	age = 0;
	preg_status = 0;
	vel = rand_direction();
	hunger = 0;
	std::random_device rd;
	death_age = rand_int(MIN_DEATH_AGE, MAX_DEATH_AGE, rd());
}


void Animal::move()
{
	pos[0] += vel[0];
	pos[1] += vel[1];
	vel = rand_direction();
}


void Animal::print_pos()
{
	std::cout << pos[0] << "," << pos[1] << std::endl;
}


bool Animal::is_pregnant()
{
	if (preg_status > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool Animal::is_due()
{
	if (preg_status == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void Animal::conceive()
{
	preg_status = PREGNANCY_PERIOD;
}


void Animal::continue_pregnancy()
{
	if (preg_status > 0)
	{
		preg_status--;
	}
}


bool Animal::is_hungry()
{
	if (hunger > 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void Animal::eat()
{
	hunger = 0;
}


void Animal::inc_hunger()
{
}


void Animal::inc_age()
{
	age++;
}


void Animal::print()
{
	std::cout << "ANIMAL" << std::endl;
}


void Animal::update()
{
	inc_age();
	inc_hunger();
	continue_pregnancy();
	move();
}


Animal::~Animal() {}
