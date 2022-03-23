/*
 *	Functions specific to the project and
 *	that use types specific to the project
 *	(eg. Animal).
 */
#pragma once
#include "includes.h"
#include "animal.h"
#include "birth.h"
#include "config.h"

void new_animal(int &id, int index, Birth new_birth, Animal* animal_list[], Config* config);
void init_animals(int n_pred, int n_prey, int &id, int &n_living, Animal* animal_list[], Config* config);

void erase_animal(int index, Animal* animal_list[]);

bool is_in_kill_list(int element, int kill_list[DEATH_LIST_LENGTH], int kill_count);

