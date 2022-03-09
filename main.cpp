#include "includes.h"
#include "animal.h"
#include "predator.h"
#include "prey.h"
#include "basic_funcs.h"
#include "sim_funcs.h"
#include <iostream>


int main()
{

	// initialising
	int id = 0; // initial id
	int n_living = 0;
	Animal* animal_list[MAX_POPULATION];
	int kill_list[MAX_DEATHS]; // animals to kill this timestep
	std::vector<std::string> birth_list;

	// better way of doing this?
	std::string label1("predator");
	std::string label2("prey");




	// make initial predators and prey
	for (int i=0; i<INITIAL_PREDATORS; i++)
	{
		new_animal(id, n_living, label1, &animal_list[0]);
		n_living++;
	}
	for (int i=0; i<INITIAL_PREY; i++)
	{
		new_animal(id, n_living, label2, &animal_list[0]);
		n_living++;
	}
	




	// main simulation loop
	for (int t=0; t<TIMESTEPS; t++)
	{

		std::cout << "----- TIMESTEP " << t << " -----"<< std::endl;
		std::cout << "Population: " << n_living << std::endl;
		std::cout << "ID: " << id << std::endl;

		// reset kill and birth counters for the timestep
		int kill_count = 0;
		int birth_count = 0;









		// calculation loop
		for (int a=0; a<n_living; a++)
		{

			// interactions with other animals
			for (int b=0; b<n_living; b++)
			{

				if (animal_list[b]->id != animal_list[a]->id)
				{
					// if ids are different

					std::string type_a = animal_list[a]->type;
					std::string type_b = animal_list[b]->type;



					if (type_a == type_b)
					{
						// if animals are the same species
						if (scalar_difference(animal_list[a]->pos, animal_list[b]->pos) < BREEDING_DISTANCE)
						{
							// breeding
							if (animal_list[a]->is_pregnant())
							{
								if (animal_list[a]->is_due())
								{
									birth_list.push_back(animal_list[a]->type);
									birth_count++;
								}
							}
							else
							{
								animal_list[a]->conceive();
							}
						}
					}
					else if (type_a == "predator")
					{
						// predator-prey interactions
						if (scalar_difference(animal_list[a]->pos, animal_list[b]->pos) < MUNCHING_DISTANCE)
						{
							// predator munches prey

							// subtract from animal's hunger and kill the prey predator's hunger
							if (animal_list[a]->is_hungry())
							{

								if (!is_in_kill_list(b, kill_list, kill_count))
								{
									// add munched prey to kill list if not already on it
									kill_list[kill_count] = b;
									kill_count++;
									animal_list[a]->eat();
									std::cout << animal_list[b]->id << " got munched!" << std::endl;
								}
							}
						}
					}
				}
			}
		} // end of calculation loop







		// add old or starved animals to the kill_list
		for (int a = 0; a < n_living; a++)
		{
			if (!is_in_kill_list(a, kill_list, kill_count))
			{
				if (animal_list[a]->age >= MAX_AGE)
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

		// new birth and death loop
		while (kill_count>0)
		{

			// used to keep kill_list correct
			int tmp1 = n_living - 1;
			int tmp2 = kill_count - 1;

			erase_animal(kill_list[kill_count-1], &animal_list[0]);
			n_living--;
			if (birth_count>0)
			{
				// fill the hole with new animal
				new_animal(id, kill_list[kill_count-1], birth_list[birth_count-1], &animal_list[0]);
				n_living++;
				birth_count--;
			}
			else
			{
				animal_list[kill_list[kill_count-1]] = animal_list[n_living];
				// if the animal that was just moved in animal_list is in kill_list,
				// we need to update its corresponding value in kill_list.
				for (int k = 0; k < kill_count; k++)
				{
					// if tmp1 is in kill_list: change it to tmp2.
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
			// add new animals to the end of animal_list
			new_animal(id, n_living, birth_list[birth_count-1], &animal_list[0]);	
			n_living++;
			birth_count--;
		}
		birth_list.clear();




		// update loop
		for (int a=0; a<n_living; a++)
		{
			animal_list[a]->update();
		}









		// break simulation loop if all animals are dead
		if (n_living == 0)
		{
			std::cout << "all dead!" << std::endl;
			std::cout << std::endl;
			break;
		}

		std::cout << std::endl;
	}



	
	/*
	// cleaning up
	destroy_animal_list(animal_list);	
	*/

	return 0;
}

