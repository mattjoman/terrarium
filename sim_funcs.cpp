/*
 *	Functions specific to the project and
 *	that use types specific to the project
 *	(eg. Animal).
 */
#include "sim_funcs.h"
#include "predator.h"
#include "prey.h"


void new_animal(int &id, std::string species, std::vector<Animal*> &animal_list) {
	std::string species1("predator");
	std::string species2("prey");

	if (species.compare(species1) == 0) {
		//std::cout << "New Predator..." << std::endl;
		Predator* animal = new Predator(id);
		animal_list.push_back(animal);
	} else if (species.compare(species2) == 0) {
		//std::cout << "New Prey..." << std::endl;
		Prey* animal = new Prey(id);
		animal_list.push_back(animal);
	}
	id++;
}


void erase_animal(std::vector<Animal*> &animal_list, std::vector<Animal*>::iterator iter) {
	std::cout << (*iter)->id << std::endl;
	delete *iter; // delete animal object
	animal_list.erase(iter); // erase the element from animal_list
}

void destroy_animal_list(std::vector<Animal*> &animal_list) {
	// delete all animals in 'animal_list' and clear the vector
	// do this at the end of the program
	for (std::vector<Animal*>::iterator it=animal_list.begin(); it!=animal_list.end(); it++) {
		//cout << (*it)->id << endl;
		delete *it;
	}
	animal_list.clear();
}

