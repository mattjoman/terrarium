#include "includes.h"
#include "animal.h"
#include "predator.h"
#include "prey.h"
#include "basic_funcs.h"
#include "sim_funcs.h"
#include "birth.h"
#include "output.h"
#include <iostream>
#include <future>


/* Runs the simulation */
void simulation(std::promise<int>&& sim_exit_code, bool *is_finished, int *current_timestep, int *current_population, int *cum_population, std::map<std::string, int>* config);
