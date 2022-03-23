#pragma once

#include "includes.h"

#define ANIMAL_LIST_LENGTH 100000
#define DEATH_LIST_LENGTH  100000

/*
struct Config
{
		int TIMESTEPS;
		int MAX_POPULATION;
		int MAX_DEATHS;
		int MIN_DEATH_AGE;
		int MAX_DEATH_AGE;
		int MAX_HUNGER;
		int BREEDING_DISTANCE;
		int MUNCHING_DISTANCE;
		int PREGNANCY_PERIOD;
		int SPAWN_RADIUS;
		int INITIAL_PREDATORS;
		int INITIAL_PREY;
};
*/

//Config_Data read_config();

//void write_config(Config_Data data);



//Config* read_config();
std::map<std::string, int>* read_config();

void write_config(std::map<std::string, int> new_config);
