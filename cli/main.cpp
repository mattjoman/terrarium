#include <iostream>
#include <string.h>
#include "app.h"

int main(int argc, char** argv)
{
	switch(argc)
	{
		case 1:
		{
			/* Run simulation, write output to ./output.dat */
			run_simulation();
			break;
		}

		case 2:
		{
			if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
			{
				/* Print help/user-guide */
				std::cout << "Help/user-guide coming soon..." << std::endl;
			}
			else if (strcmp(argv[1], "--show-config") == 0 || strcmp(argv[1], "-s") == 0)
			{
				/* Print current config */
				std::cout << "Printing current config coming soon..." << std::endl;
				display_params();
			}
			break;
		}

		case 3:
		{
			if (strcmp(argv[1], "--output-path") == 0 || strcmp(argv[1], "-o") == 0)
			{
				/* Run the simulation with the specified output file path */
				if (argv[2][0] == '/' || argv[2][0] == '~')
				{
					/* Absolute path provided */
					std::cout << "Absolute output paths coming soon..." << std::endl;
				}
				else
				{
					/* Relative path provided */
					std::cout << "Relative output paths coming soon..." << std::endl;
				}
			}
			else if (strcmp(argv[1], "--update-param") == 0 || strcmp(argv[1], "-u") == 0)
			{
				std::string param = argv[2];
				update_param(param);
			}
			break;
		}

		default:
		{
			break;
		}
	}
	return 0;
}
