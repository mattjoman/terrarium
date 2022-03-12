/*
 *	Functions specific to the project and
 *	that use types specific to the project
 *	(eg. Animal).
 */
#pragma once
#include "includes.h"
#include "animal.h"

void new_animal(int &id, int index, std::string species, Animal* animal_list[]);

void erase_animal(int index, Animal* animal_list[]);

bool is_in_kill_list(int element, int kill_list[MAX_DEATHS], int kill_count);

