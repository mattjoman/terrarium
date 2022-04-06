/*
 *	Functions specific to the project and
 *	that use types specific to the project
 *	(eg. Animal).
 */
#include "sim_funcs.h"
#include "basic_funcs.h"
#include "predator.h"
#include "prey.h"
#include "birth.h"


void new_animal(int &id, int index, Birth new_birth, Animal* animal_list[], std::map<std::string, int>* config)
{
	if (new_birth.type == "predator")
	{
		Predator* animal = new Predator(id, new_birth.pos, (*config)["MIN_DEATH_AGE"], (*config)["MAX_DEATH_AGE"]);
		animal_list[index] = animal;
	} else if (new_birth.type == "prey")
	{
		Prey* animal = new Prey(id, new_birth.pos, (*config)["MIN_DEATH_AGE"], (*config)["MAX_DEATH_AGE"]);
		animal_list[index] = animal;
	}
	id++;
	return;
}


void init_animals(int &id, int &n_living, Animal* animal_list[], std::map<std::string, int>* config)
{
	for (int i = 0; i < (*config)["INITIAL_PREDATORS"]; i++)
	{
		std::string type = "predator";
		std::vector<float> pos = rand_vector(0, (*config)["SPAWN_RADIUS"]);
		Birth new_birth(type, pos);
		new_animal(id, n_living, new_birth, &animal_list[0], config);
		n_living++;
	}
	for (int i = 0; i < (*config)["INITIAL_PREY"]; i++)
	{
		std::string type = "prey";
		std::vector<float> pos = rand_vector(0, (*config)["SPAWN_RADIUS"]);
		Birth new_birth(type, pos);
		new_animal(id, n_living, new_birth, &animal_list[0], config);
		n_living++;
	}
	return;
}


void erase_animal(int index, Animal* animal_list[])
{
	delete animal_list[index]; // delete animal object
	return;
}


bool is_in_kill_list(int element, int kill_list[DEATH_LIST_LENGTH], int kill_count)
{
	// return true if the element is in kill_list
	bool in_kill_list = false;
	for (int i = 0; i < kill_count; i++)
	{
		if (kill_list[i] == element)
		{
			in_kill_list = true;
			break;
		}
	}
	return in_kill_list;
}
