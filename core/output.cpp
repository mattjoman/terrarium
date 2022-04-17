#include <fstream>
#include "output.h"
#include "../share/includes.h"

void create_output_files(std::map<std::string, int> config, std::string output_path)
{
	/*
	 * Overwrite previous file, write the simulation params and
	 * write data column headings.
	 */

	std::fstream file;

	file.open(output_path, std::ios::out);
	file << "";
	file.close();

	return;
}


void append_animal_info(
		bool								is_last_animal,
		int 								id,
		std::string 				species,
		std::vector<float> 	pos,
		std::string					output_path
		)
{
	/*
	 * Write animal's data for the timestep.
	 *
	 */
	std::fstream file;

	if (!is_last_animal)
	{
		file.open(output_path, std::ios::out | std::ios::app);
		file << id << " " << species << " " << pos[0] << " " << pos[1] << " ";
		file.close();
	}
	else
	{
		file.open(output_path, std::ios::out | std::ios::app);
		file << id << " " << species << " " << pos[0] << " " << pos[1] << std::endl;
		file.close();
	}

	return;
}




void append_timestep_info(
		int 				timestep,
		int 				id,
		int 				n_living,
		std::string	output_path
		)
{
	/*
	 * Write timestep info (timestep, cup pop, population, prey/predator populations)
	 */
	std::fstream file;

	file.open(output_path, std::ios::out | std::ios::app);
	file << timestep << " " << id << " " << n_living << std::endl;
	file.close();

	return;
}