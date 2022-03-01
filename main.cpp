/*
 *	Breaks when:				decreasing id
 *	13 (prey) munched!				|
 *	12 (prey) munched!				v
 *	Segmentation fault (core dumped)
 *
 *	Fix:
 *	Just store ids in kill_list?
 */

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
		std::cout << "Timestep: " << t << std::endl;
		std::cout << "Animals: " << animal_list.size() << std::endl;

		// reset kill counter
		int kill_count = 0;

		// calculation loop
		for (size_t a=0; a<animal_list.size(); a++) {

			// will the animal die this timestep?
			if (animal_list[a]->age >= MAX_AGE) {
				kill_list[kill_count] = a;
				kill_count++;
				continue;
			} else if (animal_list[a]->hunger >= MAX_HUNGER) {
				kill_list[kill_count] = a;
				kill_count++;
				continue;
			}

			// interactions with other animals
			for (size_t b=0; b<animal_list.size(); b++) {

				if (animal_list[b]->id != animal_list[a]->id) {
					// if ids are different

					std::string type_a = animal_list[a]->type;
					std::string type_b = animal_list[b]->type;



					if (type_a == type_b) {
						// if animals are the same species
						if (scalar_difference(animal_list[a]->pos, animal_list[b]->pos) < BREEDING_DISTANCE) {
							// breeding
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



					} else if (type_a == "predator") {
						// predator-prey interactions
						if (scalar_difference(animal_list[a]->pos, animal_list[b]->pos) < MUNCHING_DISTANCE) {
							// predator munches prey

							// add to predator's hunger



							bool in_kill_list = false;
							for (int i = 0; i < kill_count; i++) {
								if (kill_list[i]==b) {
									in_kill_list = true;
								}
							}
							if (!in_kill_list) {
								// add munched prey to kill list if not already on it
								kill_list[kill_count] = b;
								kill_count++;
								std::cout << animal_list[b]->id << " (" << animal_list[b]->type << ")" << " munched!" << std::endl;
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

