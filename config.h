#pragma once

/*
// Maximum number of timesteps
#define TIMESTEPS 50 

// Maximum animals living at once
#define MAX_POPULATION 1000

// Maximum deaths per timestep
#define MAX_DEATHS 10000 

// Determine the life-span of animals
#define MIN_DEATH_AGE 5 // inclusive
#define MAX_DEATH_AGE 10 // exclusive

#define MAX_HUNGER 3 // maximum hunger for animals
#define BREEDING_DISTANCE 2 // max distance animals can breed across
#define MUNCHING_DISTANCE 4 // max distance at which predators can eat prey
#define PREGNANCY_PERIOD 3 // defines time between breeding and birth
#define SPAWN_RADIUS 15 // animals spawn within this radius of their birth-location
#define INITIAL_PREDATORS 7 // initial predator count
#define INITIAL_PREY 7 // initial prey count
#define FOV 10 // max distance animals can see
*/
#define ANIMAL_LIST_LENGTH 100000
#define DEATH_LIST_LENGTH  100000

//#define MIN_DEATH_AGE      5
//#define MAX_DEATH_AGE      10
//#define PREGNANCY_PERIOD   3
//#define SPAWN_RADIUS       15

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

//Config_Data read_config();

//void write_config(Config_Data data);

Config* read_config();

void write_config(Config* config);
