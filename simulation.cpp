#include "config.h"
#include "includes.h"
#include "animal.h"
#include "predator.h"
#include "prey.h"
#include "basic_funcs.h"
#include "birth.h"
#include "output.h"
#include <iostream>
#include <future>


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






void simulation(std::promise<int>&& sim_exit_code, bool *is_finished, int *current_timestep, int *current_population, int *cum_population, std::map<std::string, int>* config)
{

	// initialising
	create_output_files(config);
	int id = 0; // initial id
	int n_living = 0;
	Animal* animal_list[ANIMAL_LIST_LENGTH];
	int kill_list[DEATH_LIST_LENGTH]; // animals to kill this timestep
	std::vector<Birth> birth_list;
	int final_timestep = 0; // record the last timestep (for output file)

	// make initial predators and prey
	init_animals(id, n_living, &animal_list[0], config);


	// main simulation loop
	for (int t=0; t < (*config)["TIMESTEPS"]; t++)
	{
		/* Add the timestep, cum pop, pop to the output file */
		append_timestep_info(t, id, n_living);

		/* reset kill and birth counters for the timestep */
		int kill_count = 0;
		int birth_count = 0;









		/* Calculation loop */
		for (int a=0; a<n_living; a++)
		{

			Animal* animal_a = animal_list[a];


			/* Write to files */
			bool is_last_animal = false;
			if (a == n_living-1) { is_last_animal = true; }
			append_animal_info(is_last_animal, animal_a->id, animal_a->type, animal_a->pos);


			/* Add births to birth_list */
			if (animal_a->is_due())
			{
				Birth new_birth(animal_a->type, animal_a->pos);
				birth_list.push_back(new_birth);
				birth_count++;
			}



			/* Interactions with other animals */
			for (int b=0; b<n_living; b++)
			{

				Animal* animal_b = animal_list[b];

				if (animal_b->id != animal_a->id)
				{



					if (animal_a->type == animal_b->type)
					{
						if (scalar_difference(animal_a->pos, animal_b->pos) < (*config)["BREEDING_DISTANCE"])
						{
							/* Breeding */
							if (!animal_a->is_pregnant())
							{
								animal_a->conceive((*config)["PREGNANCY_PERIOD"]);
							}
						}
					}




					else if (animal_a->type == "predator")
					{
						if (scalar_difference(animal_a->pos, animal_b->pos) < (*config)["MUNCHING_DISTANCE"])
						{
							/* Predator munches prey */

							if (animal_a->is_hungry())
							{

								if (!is_in_kill_list(b, kill_list, kill_count))
								{
									/* Add munched prey to kill list if not already on it */
									kill_list[kill_count] = b;
									kill_count++;
									animal_a->eat();
								}
							}
						}
					}





				}
			}
		} // end of calculation loop









		/* Add old or starved animals to the kill_list */
		for (int a = 0; a < n_living; a++)
		{
			if (!is_in_kill_list(a, kill_list, kill_count))
			{
				if (animal_list[a]->age >= animal_list[a]->death_age)
				{
					kill_list[kill_count] = a;
					kill_count++;
				} else if (animal_list[a]->hunger >= (*config)["MAX_HUNGER"])
				{
					kill_list[kill_count] = a;
					kill_count++;
				}
			}
		}





		/* Guard against overpopulating animal_list */
		if (n_living + birth_count - kill_count >= (*config)["MAX_POPULATION"])
		{
			for (int a = 0; a < n_living; a++)
			{
				delete animal_list[a];
			}
			/* Return the exit code to the main thread */
			*cum_population = id;
			*is_finished = true;
			sim_exit_code.set_value(1);
			return;
		}





		/* Birth and death loop */
		while (kill_count>0)
		{

			/* Used to keep kill_list correct */
			int tmp1 = n_living - 1;
			int tmp2 = kill_count - 1;

			erase_animal(kill_list[kill_count-1], &animal_list[0]);
			n_living--;
			if (birth_count>0)
			{
				Birth new_birth = *(birth_list.end()-1);
				new_animal(id, kill_list[kill_count-1], new_birth, &animal_list[0], config);
				birth_list.pop_back();
				n_living++;
				birth_count--;
			}
			else
			{
				animal_list[kill_list[kill_count-1]] = animal_list[n_living];
				for (int k = 0; k < kill_count; k++)
				{
					if (kill_list[k] == tmp1)
					{
						kill_list[k] = tmp2;
						break;
					}
				}
			}
			kill_count--;
		}
		while (birth_count>0)
		{
			Birth new_birth = *(birth_list.end()-1);
			new_animal(id, n_living, new_birth, &animal_list[0], config);
			birth_list.pop_back();
			n_living++;
			birth_count--;
		}
		birth_list.clear();


		/* Update loop */
		for (int a=0; a<n_living; a++)
		{
			animal_list[a]->update();
		}



		// just use *current_timestep
		final_timestep++;
		*current_timestep = t;
		*current_population = n_living;


		/* Break from simulation loop and add empty line to output file (pop 0) */
		if (n_living == 0)
		{
			append_timestep_info(final_timestep, id, n_living);
			*cum_population = id;
			*is_finished = true;
			sim_exit_code.set_value(2);
			return;
		}




	}


	/* Add the timestep, cum pop, pop to the output file */
	append_timestep_info(final_timestep, id, n_living);

	
	/* Add survivors to output file and delete the animals */
	bool is_last_animal = false;
	for (int i = 0; i < n_living; i++)
	{
		if (i == n_living-1) { is_last_animal = true; }
		Animal *animal = animal_list[i];
		append_animal_info(is_last_animal, animal->id, animal->type, animal->pos);
		delete animal;
	}

	/* Return the exit code to the main thread */
	*cum_population = id;
	*is_finished = true;
	sim_exit_code.set_value(0);
	return;
}

