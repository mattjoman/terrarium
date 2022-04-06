#pragma once

#include "includes.h"
#include "animal.h"
#include "predator.h"
#include "prey.h"
#include "basic_funcs.h"
#include "birth.h"
#include "output.h"
#include <iostream>
#include <future>



void new_animal(int &id, int index, Birth new_birth, Animal* animal_list[], std::map<std::string, int>* config);

void init_animals(int &id, int &n_living, Animal* animal_list[], std::map<std::string, int>* config);

void erase_animal(int index, Animal* animal_list[]);

bool is_in_kill_list(int element, int kill_list[DEATH_LIST_LENGTH], int kill_count);

/* Runs the simulation */
void simulation(std::promise<int>&& sim_exit_code, bool *is_finished, int *current_timestep, int *current_population, int *cum_population, std::map<std::string, int>* config);



