#pragma once
#include <fstream>
#include <vector>

void create_output_files();

void append_animal_info(
		bool 								is_last_animal,
		int 								id,
		std::string 				species,
		std::vector<float> 	pos
		);

void append_timestep_info(int timestep, int id, int n_living);