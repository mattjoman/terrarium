#include "config.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

Config* read_config()
{

	Config* config = new Config;
	
	// check if the config file exists and is correct
	bool file_exists = true;

	if (file_exists)
	{
		std::fstream file;
		file.open("config.dat",std::ios::in);
		if (file.is_open())
		{
			std::string line;
			for (int i = 0; i < 12; i++)
			{
				getline(file, line);
				std::stringstream num(line);
				int val;
				num >> val;
				switch (i)
				{
				case 0:
					config->TIMESTEPS = val;
					break;
				case 1:
					config->MAX_POPULATION = val;
					break;
				case 2:
					config->MAX_DEATHS = val;
					break;
				case 3:
					config->MIN_DEATH_AGE = val;
					break;
				case 4:
					config->MAX_DEATH_AGE = val;
					break;
				case 5:
					config->MAX_HUNGER = val;
					break;
				case 6:
					config->BREEDING_DISTANCE = val;
					break;
				case 7:
					config->MUNCHING_DISTANCE = val;
					break;
				case 8:
					config->PREGNANCY_PERIOD = val;
					break;
				case 9:
					config->SPAWN_RADIUS = val;
					break;
				case 10:
					config->INITIAL_PREDATORS = val;
					break;
				case 11:
					config->INITIAL_PREY = val;
					break;
				default:
					break;
				}
			}
			file.close();   //close the file object.
		}
	}
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



	// read data from the config file and add it to the Config* object
	
	/*
	*/

	return config;
}

void write_config(Config* config)
{
}


/*
int main()
{
	Config* config = read_config();

	std::cout << config->TIMESTEPS << std::endl;

	return 0;
}
*/
