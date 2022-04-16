#include <iostream>
#include <stdio.h>
#include <future>
#include <chrono>
#include <thread>
#include <string>
#include <map>
#include "../core/simulation.h"
#include "../share/config.h"
#include "app.h"



void run_simulation()
{
	// in shared memory:
	bool *is_finished = new bool(false);
	int *current_timestep = new int(0);
	int *current_population = new int(0);
	int *cum_population = new int(0);

	// promise and future
	std::promise<int> sim_exit_code;
	std::future<int> sim_exit_code_future = sim_exit_code.get_future();
	
	// start simulation
	std::thread sim_thread(simulation, std::move(sim_exit_code), is_finished, current_timestep, current_population, cum_population);
	
	while (!*is_finished)
	{
		/*
		std::cout << "Timestep: " << *current_timestep << std::endl;
		std::cout << "Population: " << *current_population << std::endl;
		*/
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	int exit = sim_exit_code_future.get();
	sim_thread.join();

	/* Review the simulation */
	switch (exit)
	{
	case 0:
		std::cout << "Exit code 0: Simulation completed successfully." << std::endl;
		break;
	case 1:
		std::cout << "Exit code 1: Simulation stopped early due to high population." << std::endl;
		break;
	case 2:
		std::cout << "Exit code 2: Simulation stopped early because everything died." << std::endl;
		break;
	default:
		break;
	}

	/* Clean up heap variables */
	delete is_finished;
	delete current_timestep;
	delete current_population;
	delete cum_population;
}


void display_params()
{
	const int total_line_len = 28; // total length of lines displayed including separating white spaces
	const int max_param_len  = 17; // length of longest parameter name
	const int max_value_len  =  7; // length of longest allowed value

	std::cout << std::endl;

	std::map<std::string, int> config = read_config();
	for (auto itr = config.begin(); itr != config.end(); itr++)
	{
		size_t param_len = (*itr).first.size();
		int white_spaces = total_line_len - max_param_len - 1;

		white_spaces += max_param_len - (int)param_len;

		/* Adjust white_spaces according to number of digits in (*itr).second */
		for (long long n = 10; n <= (*itr).second; n *= 10)
			white_spaces--;

		std::cout << (*itr).first;
		for (int i = 0; i < white_spaces; i++)
			putchar(' ');
		std::cout << (*itr).second << std::endl;
	}
	std::cout << std::endl;
}


void edit_param(std::string param_name, int new_value)
{
	std::map<std::string, int> config = read_config();
	if (config.count(param_name))
	{
		config[param_name] = new_value;
		write_config(config);
		std::cout << param_name << " set to " << new_value << std::endl;
	}
	else
	{
		std::cout << param_name << " is not a parameter" << std::endl;
	}
}


void print_help()
{
	std::cout << "Description:" << std::endl;
	std::cout << "Arguments:" << std::endl;
	std::cout << "Examples:" << std::endl;
}
