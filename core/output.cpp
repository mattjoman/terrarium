#include <fstream>
#include "output.h"
#include "sim_data.h"
#include "../share/includes.h"

void create_output_files()
{
	/*
	 * Overwrite previous file, write the simulation params and
	 * write data column headings.
	 */

	extern std::string OUTPUT_PATH;
	std::fstream file;

	file.open(OUTPUT_PATH, std::ios::out);
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




void append_timestep_info(int t, Simulation_Data s_data)
{
	/*
	 * Write timestep info (timestep, cum pop, population, prey/predator populations)
	 */

	extern std::string OUTPUT_PATH;

	std::fstream file;

	file.open(OUTPUT_PATH, std::ios::out | std::ios::app);
	file << t << " " << s_data.id << " " << s_data.n_living << " " << s_data.n_preds << " " << s_data.n_prey << std::endl;
	file.close();

	return;
}
