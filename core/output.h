#pragma once
#include <fstream>
#include <vector>
#include "sim_data.h"
#include "../share/config.h"

void create_output_files();

void append_animal_info(
		bool 								is_last_animal,
		int 								id,
		std::string 				species,
		std::vector<float> 	pos,
		std::string					output_path
		);

void append_timestep_info(int t, Simulation_Data s_data);
