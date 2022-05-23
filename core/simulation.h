#pragma once

#include "../share/includes.h"
#include "animal.h"
#include "predator.h"
#include "prey.h"
#include "basic_funcs.h"
#include "birth.h"
#include "output.h"
#include "sim_data.h"
#include <iostream>
#include <future>



/*
 * Creates a new Animal* and puts it in animal_list[index].
 * Does not update any other simulation data.
 */
void new_animal(
		int                        id,
		int                        index,
		Birth                      new_birth,
		Animal**                   animal_list
		);



/*
 * Initialises the first predators and prey.
 * s_data.id and s_data.n_living are updated.
 * Calls new_animal() the required number of times for predators and prey.
 */
void init_animals(
		Simulation_Data            &s_data,
		Animal**                    animal_list
		);



/*
 */
void erase_animal(int index, Animal** animal_list);

/*
 */
bool is_in_kill_list(int element, int kill_list[DEATH_LIST_LENGTH], int kill_count);

/*
 * add
 */
void do_births_and_deaths(
		Simulation_Data &s_data,
		int* kill_list,
		Animal** animal_list,
		std::vector<Birth> &birth_list
		);

/*
 * add
 */
void animal_interactions(
		Simulation_Data &s_data,
		int* kill_list,
		Animal** animal_list,
		std::vector<Birth> &birth_list
		);

void old_and_hungry(
		Simulation_Data &s_data,
		int* kill_list,
		Animal** animal_list
		);

void update_animals(Simulation_Data& s_data, Animal** animal_list);

void prepare_for_exit(
		Simulation_Data& s_data,
		bool* is_finished,
		int* cum_population
		);


/*
 */
void simulation(
		std::promise<int>&& sim_exit_code,
		bool                *is_finished,
		int                 *current_timestep,
		int                 *current_population,
		int                 *cum_population
		);



