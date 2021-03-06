#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include "app.h"

#define CWD_BUF_SIZE 64



int main(int argc, char** argv)
{

	if (argc < 2)
	{
		/* Run help function */
		std::string help_path = getenv("HOME");
		help_path += "/.config/terrarium/help.txt";
		print_file(help_path);
		exit(0);
	}




	if (strcmp(argv[1], "run") == 0)
	{
		/* Command is terrarium run */
		std::cout << "Preparing to run simulation..." << std::endl;

		/* Prepare and run the simulation... */
		const char* output_path_arg = "output.dat";

		for (int i = 2; i < argc; i++)
		{
			if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output-path") == 0)
			{
				output_path_arg = argv[i+1];
			}
		}

		run_simulation(output_path_arg);
		exit(0);
	}




	/* Command is terrarium (don't run) */

	switch (argc)
	{
		case 2:
			if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
			{
				/* Call function print_help() and exit */
				std::string help_path = getenv("HOME");
				help_path += "/.config/terrarium/help.txt";
				print_file(help_path);
				exit(0);
			}
			else if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--display-params") == 0)
			{
				/* Call function display_params() and exit */
				display_params();
				exit(0);
			}
			else if (strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "--info") == 0)
			{
				/* Call function display_params() and exit */
				std::string info_path = getenv("HOME");
				info_path += "/.config/terrarium/info.txt";
				print_file(info_path);
				exit(0);
			}
			else
			{
				std::cout << "Error" << std::endl;
				exit(1);
			}
			break;
		case 3:
			if (strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "--edit-param") == 0)
			{
				/* Get the arg and split it into 'param_name' and 'new_value' */
				std::string arg = argv[2];
				std::size_t equals = arg.find("=");
				std::string param_name = arg.substr(0, equals);
				std::string new_value_str = arg.substr(equals+1);
				int new_value = std::stoi(new_value_str);
				for (int i = 0; i < param_name.size(); i++)
				{
					param_name[i] = std::toupper((int)param_name[i]);
				}
				edit_param(param_name, new_value);
			}
			else
			{
				std::cout << "Error" << std::endl;
				exit(1);
			}
			break;
		default:
			std::cout << "Invalid number of arguments" << std::endl;
			exit(1);
			break;
	}

	return 1;
}
