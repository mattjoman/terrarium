#include "includes.h"
#include "animal.h"
#include "predator.h"
#include "prey.h"
#include "basic_funcs.h"
#include "sim_funcs.h"
#include <iostream>


int main() {

	// initialising
	int id = 0; // initial id
	std::vector<Animal*> animal_list;
	size_t kill_list[MAX_DEATHS]; // animals to kill this timestep
	std::vector<std::string> birth_list;

	// declare an iterator variable
	std::vector<Animal*>::iterator iter;

	// better way of doing this?
	std::string label1("predator");
	std::string label2("prey");




	// make initial predators and prey
	for (int i=0; i<INITIAL_PREDATORS; i++) {
		new_animal(id, label1, animal_list);
	}
	for (int i=0; i<INITIAL_PREY; i++) {
		new_animal(id, label2, animal_list);
	}
	




	// main simulation loop
	for (int t=0; t<TIMESTEPS; t++) {
		std::cout << "Timestep " << t << std::endl;

		int kill_count = 0;

		// calculation loop
		for (size_t a=0; a<animal_list.size(); a++) {
			if (animal_list[a]->age >= MAX_AGE) {
				kill_list[kill_count] = a;
				kill_count++;
				continue;
			} else if (animal_list[a]->hunger >= MAX_HUNGER) {
				kill_list[kill_count] = a;
				kill_count++;
				continue;
			}

			for (size_t b=0; b<animal_list.size(); b++) {
				if (animal_list[b]->type == animal_list[a]->type && animal_list[b]->id != animal_list[a]->id) {

					// breeding
					if (scalar_difference(animal_list[a]->pos, animal_list[b]->pos) < BREEDING_DISTANCE) {
						if (animal_list[a]->preg_status == 0) {
							animal_list[a]->preg_status = PREGNANCY_PERIOD;
						} else if (animal_list[a]->preg_status == 1) {
							if (animal_list[a]->type == "predator") {
								birth_list.push_back("predator");
							} else if (animal_list[a]->type == "prey") {
								birth_list.push_back("prey");
							}
						}
					}
				}
			}
		}


		// update loop
		for (size_t a=0; a<animal_list.size(); a++) {
			animal_list[a]->move();	
			animal_list[a]->vel = rand_direction();
			animal_list[a]->age++;
			animal_list[a]->hunger++;
			if (animal_list[a]->preg_status > 0) {
				animal_list[a]->preg_status--;
			}
		}

		// birth loop
		if (birth_list.size() > 0) {
			for (size_t a=0; a<birth_list.size(); a++) {
				new_animal(id, birth_list[a], animal_list);			
			}
			birth_list.clear();
		}


		// kill loop
		if (kill_count > 0) {
			for (int a=kill_count-1; a>=0; a--) {
				iter = animal_list.begin() + kill_list[a];
				erase_animal(animal_list, iter);
			}
		}

		// break simulation loop if all animals are dead
		if (animal_list.size() == 0) {
			std::cout << "all dead!" << std::endl;
			break;
		}
	}



	
	// cleaning up
	destroy_animal_list(animal_list);	

	return 0;
}

