#include "config.h"
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>

std::map<std::string, int> read_config()
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

	std::map<std::string, int> config;
	
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
				config[keys[i]] = val; // add key-val pair to the config map
			}
			file.close();   //close the file object.
		}
	}
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
