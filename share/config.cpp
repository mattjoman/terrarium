#include "config.h"
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <string.h>

#include <iostream>
#include <unistd.h>


/* Globals */
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


/*
 * Helper function.
 */
int get_num(std::fstream& file)
{
	std::string line;
	getline(file, line);
	std::stringstream num(line);
	int val;
	num >> val;
	return val;
}

void read_config_global()
{

	std::fstream file;

	std::string home = getenv("HOME");
	std::string config_path = home + "/.config/terrarium/config.dat";

	file.open(config_path, std::ios::in);

	TIMESTEPS         = get_num(file);
	MAX_POPULATION    = get_num(file);
	MAX_DEATHS        = get_num(file);
	MIN_DEATH_AGE     = get_num(file);
	MAX_DEATH_AGE     = get_num(file);
	MAX_HUNGER        = get_num(file);
	BREEDING_DISTANCE = get_num(file);
	MUNCHING_DISTANCE = get_num(file);
	PREGNANCY_PERIOD  = get_num(file);
	SPAWN_RADIUS      = get_num(file);
	INITIAL_PREDATORS = get_num(file);
	INITIAL_PREY      = get_num(file);

	file.close();
}


std::map<std::string, int> read_config()
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

	std::map<std::string, int> config;
	
	std::fstream file;

	/*
	char* home = getenv("HOME");
	const char* config_path = strcat(home, "/.config/terrarium/config.dat");
	*/
	std::string home = getenv("HOME");
	std::string config_path = home + "/.config/terrarium/config.dat";

	file.open(config_path, std::ios::in);

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

	std::string home = getenv("HOME");
	std::string config_path = home + "/.config/terrarium/config.dat";

	file.open(config_path, std::ios::out);
	file << "";
	file.close();
	file.open(config_path, std::ios::out | std::ios::app);
	for (int i = 0; i < keys.size(); i++)
	{
		file << new_config[keys[i]] << std::endl;
	}
	file.close();
}
