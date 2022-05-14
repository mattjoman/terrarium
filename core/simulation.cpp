#include "../share/config.h"
#include "animal.h"
#include "predator.h"
#include "prey.h"
#include "basic_funcs.h"
#include "birth.h"
#include "output.h"
#include <future>
#include "../share/includes.h"
#include "sim_data.h"



void new_animal(int id, int index, Birth new_birth, Animal** animal_list, std::map<std::string, int> config)
{
	if (new_birth.type == "predator")
	{
		Predator* animal = new Predator(id, new_birth.pos, config["MIN_DEATH_AGE"], config["MAX_DEATH_AGE"]);
		animal_list[index] = animal;
	} else if (new_birth.type == "prey")
	{
		Prey* animal = new Prey(id, new_birth.pos, config["MIN_DEATH_AGE"], config["MAX_DEATH_AGE"]);
		animal_list[index] = animal;
	}
	return;
}


void init_animals(Simulation_Data &s_data, Animal** animal_list, std::map<std::string, int> config)
{
	for (int i = 0; i < config["INITIAL_PREDATORS"]; i++)
	{
		std::string type = "predator";
		std::vector<float> pos = rand_vector(0, config["SPAWN_RADIUS"]);
		Birth new_birth(type, pos);
		new_animal(s_data.id, s_data.n_living, new_birth, animal_list, config);
		s_data.n_living++;
		s_data.id++;
	}
	for (int i = 0; i < config["INITIAL_PREY"]; i++)
	{
		std::string type = "prey";
		std::vector<float> pos = rand_vector(0, config["SPAWN_RADIUS"]);
		Birth new_birth(type, pos);
		new_animal(s_data.id, s_data.n_living, new_birth, animal_list, config);
		s_data.n_living++;
		s_data.id++;
	}
	return;
}



void erase_animal(int index, Animal** animal_list)
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








void do_births_and_deaths(
		Simulation_Data &s_data,
		int* kill_list,
		Animal** animal_list,
		std::vector<Birth> &birth_list,
		std::map<std::string, int> config
		)
{
	while (s_data.kill_count>0)
	{
		int tmp1 = s_data.n_living - 1;
		int tmp2 = s_data.kill_count - 1;
		erase_animal(kill_list[s_data.kill_count-1], animal_list);
		s_data.n_living--;
		if (s_data.birth_count>0)
		{
			Birth new_birth = *(birth_list.end()-1);
			new_animal(s_data.id, kill_list[s_data.kill_count-1], new_birth, animal_list, config);
			birth_list.pop_back();
			s_data.n_living++;
			s_data.id++;
			s_data.birth_count--;
		}
		else
		{
			animal_list[kill_list[s_data.kill_count-1]] = animal_list[s_data.n_living];
			for (int k = 0; k < s_data.kill_count; k++)
			{
				if (kill_list[k] == tmp1)
				{
					kill_list[k] = tmp2;
					break;
				}
			}
		}
		s_data.kill_count--;
	}
	while (s_data.birth_count>0)
	{
		Birth new_birth = *(birth_list.end()-1);
		new_animal(s_data.id, s_data.n_living, new_birth, animal_list, config);
		birth_list.pop_back();
		s_data.n_living++;
		s_data.id++;
		s_data.birth_count--;
	}
	birth_list.clear();
	return;
}







void animal_interactions(
		Simulation_Data &s_data,
		int* kill_list,
		Animal** animal_list,
		std::vector<Birth> &birth_list,
		std::map<std::string, int> config
		)
{
	for (int a=0; a < s_data.n_living; a++)
	{
		Animal* animal_a = animal_list[a];

		/* Add births to birth_list */
		if (animal_a->is_due())
		{
			Birth new_birth(animal_a->type, animal_a->pos);
			birth_list.push_back(new_birth);
			s_data.birth_count++;
		}

		/* Interactions with other animals */
		for (int b=0; b < s_data.n_living; b++)
		{
			Animal* animal_b = animal_list[b];
			if (animal_b->id != animal_a->id)
			{
				if (animal_a->type == animal_b->type)
				{
					if (scalar_difference(animal_a->pos, animal_b->pos) < config["BREEDING_DISTANCE"])
					{
						/* Breeding */
						if (!animal_a->is_pregnant())
						{
							animal_a->conceive(config["PREGNANCY_PERIOD"]);
						}
					}
				}
				else if (animal_a->type == "predator")
				{
					if (scalar_difference(animal_a->pos, animal_b->pos) < config["MUNCHING_DISTANCE"])
					{
						/* Predator munches prey */
						if (animal_a->is_hungry())
						{
							if (!is_in_kill_list(b, kill_list, s_data.kill_count))
							{
								/* Add munched prey to kill list if not already on it */
								kill_list[s_data.kill_count] = b;
								s_data.kill_count++;
								animal_a->eat();
							}
						}
					}
				}
			}
		}
	}
}




void old_and_hungry(
		Simulation_Data &s_data,
		int* kill_list,
		Animal** animal_list,
		std::map<std::string, int> config
		)
{
	for (int a = 0; a < s_data.n_living; a++)
	{
		if (!is_in_kill_list(a, kill_list, s_data.kill_count))
		{
			if (animal_list[a]->age >= animal_list[a]->death_age)
			{
				kill_list[s_data.kill_count] = a;
				s_data.kill_count++;
			} else if (animal_list[a]->hunger >= config["MAX_HUNGER"])
			{
				kill_list[s_data.kill_count] = a;
				s_data.kill_count++;
			}
		}
	}
}



void update_animals(Simulation_Data& s_data, Animal** animal_list)
{
	s_data.n_preds = 0;
	s_data.n_prey  = 0;
	for (int a=0; a < s_data.n_living; a++)
	{
		animal_list[a]->update();
		if (animal_list[a]->type == "predator")
			s_data.n_preds++;
		else
			s_data.n_prey++;
	}
}




void prepare_for_exit(Simulation_Data& s_data, bool* is_finished, int* cum_population)
{
	*cum_population = s_data.id;
	*is_finished = true;
}











void simulation(std::promise<int>&& sim_exit_code, bool *is_finished, int *current_timestep, int *current_population, int *cum_population, std::string output_path)
{
	std::map<std::string, int> config = read_config();	
	create_output_files(config, output_path);

	Simulation_Data s_data;

	s_data.n_preds        = config["INITIAL_PREDATORS"];
	s_data.n_prey         = config["INITIAL_PREY"];
	s_data.id             = 0;
	s_data.n_living       = 0;
	s_data.kill_count     = 0;
	s_data.birth_count    = 0;

	Animal* animal_list[ANIMAL_LIST_LENGTH];
	int kill_list[DEATH_LIST_LENGTH];                  // animals to kill this timestep
	std::vector<Birth> birth_list;

	init_animals(s_data, animal_list, config);

	/* main simulation loop */
	for (int t=0; t < config["TIMESTEPS"]; t++)
	{
		s_data.kill_count = 0;
		s_data.birth_count = 0;

		append_timestep_info(t, s_data, output_path);

		animal_interactions(s_data, kill_list, animal_list, birth_list, config);
		old_and_hungry(s_data, kill_list, animal_list, config);

		/* If there will be too many animals, exit before adding them to animal_list. */
		if (s_data.n_living + s_data.birth_count - s_data.kill_count >= config["MAX_POPULATION"])
		{
			for (int a = 0; a < s_data.n_living; a++)
				delete animal_list[a];
			prepare_for_exit(s_data, is_finished, cum_population);
			sim_exit_code.set_value(1);
			return;
		}

		do_births_and_deaths(s_data, kill_list, animal_list, birth_list, config);
		update_animals(s_data, animal_list);

		*current_timestep = t + 1;
		*current_population = s_data.n_living;

		/* Exit early if everything is dead. */
		if (s_data.n_living == 0)
		{
			append_timestep_info(t, s_data, output_path);
			prepare_for_exit(s_data, is_finished, cum_population);
			sim_exit_code.set_value(2);
			return;
		}
	}

	append_timestep_info(*current_timestep, s_data, output_path);
	
	for (int i = 0; i < s_data.n_living; i++)
	{
		Animal* animal = animal_list[i];
		delete animal;
	}
	prepare_for_exit(s_data, is_finished, cum_population);
	sim_exit_code.set_value(0);
	return;
}

