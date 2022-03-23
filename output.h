#pragma once
#include <fstream>
#include <vector>
#include "config.h"

void create_output_files(std::map<std::string, int>* config);

void append_animal_info(
		bool 								is_last_animal,
		int 								id,
		std::string 				species,
		std::vector<float> 	pos
		);

void append_timestep_info(int timestep, int id, int n_living);
