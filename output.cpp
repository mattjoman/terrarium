#include <fstream>
#include <vector>
#include "output.h"
#include "includes.h"

void create_output_file(std::string fname)
{
	/*
	 * Overwrite previous file, write the simulation params and
	 * write data column headings.
	 */

	std::fstream file;

	file.open("out.dat", std::ios::out);
	file << "";
	file.close();

	file.open(fname, std::ios::out | std::ios::app);
	file << "MAX_TIMESTEPS " << TIMESTEPS << std::endl;
	file << "" << std::endl;
	file << "timestep id species x y" << std::endl;
	file.close();

	return;
}


void append_output_file(
		std::string fname,
		int timestep,
		int id,
		std::string species,
		std::vector<float> pos
		)
{
	/*
	 * Write animal's data for the timestep.
	 */
	std::fstream file;

	file.open(fname, std::ios::out | std::ios::app);
	file << timestep << " " << id << " " << species << " " << pos[0] << " " << pos[1] << std::endl;
	file.close();

	return;
}
