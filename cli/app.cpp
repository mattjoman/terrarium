#include <iostream>
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
	std::map<std::string, int> config = read_config();
	for (auto itr = config.begin(); itr != config.end(); itr++)
	{
		std::cout << (*itr).first << "\t\t" << (*itr).second << std::endl;
	}
}


void update_param(std::string param)
{
	std::size_t equals = param.find("=");
	std::string param_name = param.substr(0, equals);
	std::string new_value_str = param.substr(equals+1);
	int new_value = std::stoi(new_value_str);
	std::map<std::string, int> config = read_config();
	for (int i = 0; i < param_name.size(); i++)
	{
		param_name[i] = std::toupper((int)param_name[i]);
	}
	if (config.count(param_name))
	{
		config[param_name] = new_value;
		write_config(config);
	}
	else
	{
		std::cout << param_name << " is not a parameter" << std::endl;
	}
}
