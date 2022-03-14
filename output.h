#pragma once
#include <fstream>
#include <vector>

void create_output_file(std::string fname);

void append_output_file(
		std::string fname,
		int timestep,
		int id,
		std::string species,
		std::vector<float> pos
		);
