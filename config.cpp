#include "config.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "includes.h"

std::map<std::string, int>* read_config()
{

	//Config* config = new Config;
	//
	std::vector<std::string> keys = 
	{
		"TIMESTEPS",
		"MAX_POPULATION",
		"MAX_DEATHS",
		"MIN_DEATH_AGE",
		"MAX_DEATH_AGE",
		"MAX_HUNGER",
		"BREEDING_DISTANCE",
		"MUNCHING_DISTANCE",
		"PREGNANCY_PERIOD",
		"SPAWN_RADIUS",
		"INITIAL_PREDATORS",
		"INITIAL_PREY"
	};

	std::map<std::string, int>* config = new std::map<std::string, int>;
	
	// check if the config file exists and is correct
	bool file_exists = true;

	if (file_exists)
	{
		std::fstream file;
		file.open("config.dat",std::ios::in);
		if (file.is_open())
		{
			std::string line;
			for (int i = 0; i < keys.size(); i++)
			{
				getline(file, line);
				std::stringstream num(line);
				int val;
				num >> val;
				(*config)[keys[i]] = val; // add key-val pair to the config map
			}
			file.close();   //close the file object.
		}
	}
	/*
	else
	{
		config->TIMESTEPS = 50;
		config->MAX_POPULATION = 1000;
		config->MAX_DEATHS = 1000;
		config->MIN_DEATH_AGE = 5;
		config->MAX_DEATH_AGE = 10;
		config->MAX_HUNGER = 3;
		config->BREEDING_DISTANCE = 2;
		config->MUNCHING_DISTANCE = 4;
		config->PREGNANCY_PERIOD = 3;
		config->SPAWN_RADIUS = 15;
		config->INITIAL_PREDATORS = 7;
		config->INITIAL_PREY = 7;
	}
	*/



	// read data from the config file and add it to the Config* object
	
	/*
	*/

	return config;
}

void write_config(std::map<std::string, int> new_config)
{
	std::vector<std::string> keys = 
	{
		"TIMESTEPS",
		"MAX_POPULATION",
		"MAX_DEATHS",
		"MIN_DEATH_AGE",
		"MAX_DEATH_AGE",
		"MAX_HUNGER",
		"BREEDING_DISTANCE",
		"MUNCHING_DISTANCE",
		"PREGNANCY_PERIOD",
		"SPAWN_RADIUS",
		"INITIAL_PREDATORS",
		"INITIAL_PREY"
	};

	std::fstream file;

	file.open("config.dat", std::ios::out);
	file << "";
	file.close();
	file.open("config.dat", std::ios::out | std::ios::app);
	for (int i = 0; i < keys.size(); i++)
	{
		file << new_config[keys[i]] << std::endl;
	}
	file.close();
}


/*
int main()
{
	Config* config = read_config();

	std::cout << config->TIMESTEPS << std::endl;

	return 0;
}
*/
