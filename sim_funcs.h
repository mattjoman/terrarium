/*
 *	Functions specific to the project and
 *	that use types specific to the project
 *	(eg. Animal).
 */
#pragma once
#include "includes.h"
#include "animal.h"

/*
void new_animal(int &id, std::string species, std::vector<Animal*> &animal_list);

void erase_animal(std::vector<Animal*> &animal_list, std::vector<Animal*>::iterator iter);

void destroy_animal_list(std::vector<Animal*> &animal_list);
*/

void new_animal(int &id, int &n_living, std::string species, Animal* animal_list[]);

void erase_animal(int &n_living, Animal* animal_list[], int index);

//void destroy_animal_list(std::vector<Animal*> &animal_list);
