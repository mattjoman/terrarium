#include "includes.h"
#include "animal.h"
#include "predator.h"
#include "prey.h"
#include "basic_funcs.h"
#include "sim_funcs.h"
#include "birth.h"
#include "output.h"
#include <iostream>


int main()
{

	// initialising
	create_output_files();
	int id = 0; // initial id
	int n_living = 0;
	Animal* animal_list[MAX_POPULATION];
	int kill_list[MAX_DEATHS]; // animals to kill this timestep
	std::vector<Birth> birth_list;
	int final_timestep = 0; // record the last timestep (for output file)

	// make initial predators and prey
	init_animals(INITIAL_PREDATORS, INITIAL_PREY, id, n_living, &animal_list[0]);


	// main simulation loop
	for (int t=0; t<TIMESTEPS; t++)
	{
		std::cout << "----- TIMESTEP " << t << " -----"<< std::endl;
		std::cout << "Population: " << n_living << std::endl;
		std::cout << "ID: " << id << std::endl;

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
						if (scalar_difference(animal_a->pos, animal_b->pos) < BREEDING_DISTANCE)
						{
							/* Breeding */
							if (!animal_a->is_pregnant())
							{
								animal_a->conceive();
							}
						}
					}




					else if (animal_a->type == "predator")
					{
						if (scalar_difference(animal_a->pos, animal_b->pos) < MUNCHING_DISTANCE)
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
									std::cout << animal_b->id << " got munched!" << std::endl;
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
					std::cout << animal_list[a]->id << " died of old age" << std::endl;
					kill_list[kill_count] = a;
					kill_count++;
				} else if (animal_list[a]->hunger >= MAX_HUNGER)
				{
					std::cout << animal_list[a]->id << " died of hunger" << std::endl;
					kill_list[kill_count] = a;
					kill_count++;
				}
			}
		}







		std::cout << "Births: " << birth_count << std::endl;
		std::cout << "Deaths: " << kill_count << std::endl;

		if (n_living + birth_count - kill_count >= MAX_POPULATION)
		{
			std::cout << "Too many animals!" << std::endl;
			exit(0);
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
				new_animal(id, kill_list[kill_count-1], new_birth, &animal_list[0]);
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
			new_animal(id, n_living, new_birth, &animal_list[0]);
			birth_list.pop_back();
			n_living++;
			birth_count--;
		}
		birth_list.clear();
		if (birth_list.size() == 0 && birth_count == 0)
		{
			std::cout << "Great success!" << std::endl;
		}





		/* Update loop */
		for (int a=0; a<n_living; a++)
		{
			animal_list[a]->update();
		}



		final_timestep++;


		/* Break from simulation loop and add empty line to output file (pop 0) */
		if (n_living == 0)
		{
			std::cout << "all dead!" << std::endl;
			std::cout << std::endl;
			break;
		}




		std::cout << std::endl;
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
	std::cout << "exiting..." << std::endl;
	std::cout << std::endl;

	return 0;
}

