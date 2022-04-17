#pragma once
#include <fstream>
#include <vector>
#include "../share/config.h"

void create_output_files(std::map<std::string, int> config, std::string output_path);

void append_animal_info(
		bool 								is_last_animal,
		int 								id,
		std::string 				species,
		std::vector<float> 	pos,
		std::string					output_path
		);

void append_timestep_info(int timestep, int id, int n_living, std::string output_path);
