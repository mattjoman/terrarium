#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <ncurses.h>
#include "simulation.h"
#include "config.h"
#include "app.h"
using namespace std;



void run_simulation(int highlight, int y_max, int x_max)
{
	// in shared memory:
	Config* config = read_config();
	bool *is_finished = new bool(false);
	int *current_timestep = new int(0);
	int *current_population = new int(0);
	int *cum_population = new int(0);

	// promise and future
	std::promise<int> sim_exit_code;
	std::future<int> sim_exit_code_future = sim_exit_code.get_future();
	
	// start simulation
	std::thread sim_thread(simulation, std::move(sim_exit_code), is_finished, current_timestep, current_population, cum_population, config);
	
	// create window for displaying simulation progress
	WINDOW *simwin = newwin(6, x_max-12, y_max-8, 5);
	box(simwin, 0, 0);
	//refresh();
	wrefresh(simwin);

	while (!*is_finished)
	{
		wclear(simwin);
		mvwprintw(simwin, 1, 1, "Timestep:    %d", *current_timestep);
		mvwprintw(simwin, 2, 1, "Population:  %d", *current_population);
		refresh();
		wrefresh(simwin);
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	// destroy the window
	delwin(simwin);
	clear();


	int exit = sim_exit_code_future.get();
	sim_thread.join();

	/* Review the simulation */
	WINDOW *reviewwin = newwin(7, x_max-12, y_max-8, 5);
	box(reviewwin, 0, 0);

	switch (exit)
	{
	case 0:
		mvwprintw(reviewwin, 1, 1, "Exit code 0: Simulation completed successfully.");
		break;
	case 1:
		mvwprintw(reviewwin, 1, 1, "Exit code 1: Simulation stopped early due to high population.");
		break;
	case 2:
		mvwprintw(reviewwin, 1, 1, "Exit code 2: Simulation stopped early because everything died.");
		break;
	default:
		break;
	}
	mvwprintw(reviewwin, 3, 1, "Timesteps computed:       %d", *current_timestep + 1);
	mvwprintw(reviewwin, 4, 1, "Cumulative population:    %d", *cum_population);
	mvwprintw(reviewwin, 5, 1, "Final population:         %d", *current_population);

	refresh();
	wrefresh(reviewwin);

	getch();

	delwin(reviewwin);
	clear();


	/* Clean up heap variables */
	delete is_finished;
	delete current_timestep;
	delete current_population;
	delete cum_population;
	delete config;
}











int get_new_val(WINDOW* editorwin, int position)
{
	mvwprintw(editorwin, 16, 1, "New val: ");
	mvwprintw(editorwin, 16, 10, "_");
	std::vector<int> numbers;
	int input_loc = 0;
	bool receiving = true;
	int raw_input;
	int input_val;

	while (receiving)
	{
		wrefresh(editorwin);
		raw_input = getch();
		if (raw_input == 10)
		{
			for (int i = 1; i < 31; i++)
			{
				mvwprintw(editorwin, 16, i, " ");
			}
			wrefresh(editorwin);
			receiving = false;
		}
		else if (raw_input == 127 && input_loc > 0)
		{
			numbers.pop_back();
			mvwprintw(editorwin, 16, 10 + input_loc, " ");
			mvwprintw(editorwin, 16, 10 + input_loc - 1, "_");
			input_loc--;
		}
		else if (raw_input >= 48 && raw_input <= 57)
		{
			input_loc++;
			input_val = raw_input - 48;
			numbers.push_back(input_val);
			mvwprintw(editorwin, 16, 10 + input_loc - 1, "%d", input_val);
			mvwprintw(editorwin, 16, 10 + input_loc, "_");
		}
	}

	int sum = 0;
	if (numbers.size() > 0)
	{
		int multiplier = 1;
		for (int i = numbers.size() - 1; i >= 0; i--)
		{
			sum += numbers[i] * multiplier;
			multiplier *= 10;
		}
	}

	// set the val
	return sum;
}




void display_new_val(WINDOW* editorwin, int position, int new_val)
{
	for (int i = 0; i < 10; i++)
	{
		mvwprintw(editorwin, position + 3, i + 61, " ");
	}
	mvwprintw(editorwin, position + 3, 61, "%d", new_val);
	wrefresh(editorwin);
}








void edit_params(int y_max, int x_max)
{
	WINDOW *editorwin = newwin(20, x_max-12, y_max-22, 5);
	box(editorwin, 0, 0);
	refresh();
	wrefresh(editorwin);

	// read the config file
	Config* config = read_config();

	// display the current config values
	mvwprintw(editorwin,  1, 1, "Current config:");
	mvwprintw(editorwin,  3, 1, "TIMESTEPS            %d", config->TIMESTEPS);
	mvwprintw(editorwin,  4, 1, "MAX_POPULATION       %d", config->MAX_POPULATION);
	mvwprintw(editorwin,  5, 1, "MAX_DEATHS           %d", config->MAX_DEATHS);
	mvwprintw(editorwin,  6, 1, "MIN_DEATH_AGE        %d", config->MIN_DEATH_AGE);
	mvwprintw(editorwin,  7, 1, "MAX_DEATH_AGE        %d", config->MAX_DEATH_AGE);
	mvwprintw(editorwin,  8, 1, "MAX_HUNGER           %d", config->MAX_HUNGER);
	mvwprintw(editorwin,  9, 1, "BREEDING_DISTANCE    %d", config->BREEDING_DISTANCE);
	mvwprintw(editorwin, 10, 1, "MUNCHING_DISTANCE    %d", config->MUNCHING_DISTANCE);
	mvwprintw(editorwin, 11, 1, "PREGNANCY_PERIOD     %d", config->PREGNANCY_PERIOD);
	mvwprintw(editorwin, 12, 1, "SPAWN_RADIUS         %d", config->SPAWN_RADIUS);
	mvwprintw(editorwin, 13, 1, "INITIAL_PREDATORS    %d", config->INITIAL_PREDATORS);
	mvwprintw(editorwin, 14, 1, "INITIAL_PREY         %d", config->INITIAL_PREY);

	// set and display the new config values
	mvwprintw(editorwin,  1, 40, "New config:");
	int new_timesteps = config->TIMESTEPS;                 display_new_val(editorwin,  0, new_timesteps);
	int new_max_population = config->MAX_POPULATION;       display_new_val(editorwin,  1, new_max_population);
	int new_max_deaths = config->MAX_DEATHS;               display_new_val(editorwin,  2, new_max_deaths);
	int new_min_death_age = config->MIN_DEATH_AGE;         display_new_val(editorwin,  3, new_min_death_age);
	int new_max_death_age = config->MAX_DEATH_AGE;         display_new_val(editorwin,  4, new_max_death_age);
	int new_max_hunger = config->MAX_HUNGER;               display_new_val(editorwin,  5, new_max_hunger);
	int new_breeding_distance = config->BREEDING_DISTANCE; display_new_val(editorwin,  6, new_breeding_distance);
	int new_munching_distance = config->MUNCHING_DISTANCE; display_new_val(editorwin,  7, new_munching_distance);
	int new_pregnancy_period = config->PREGNANCY_PERIOD;   display_new_val(editorwin,  8, new_pregnancy_period);
	int new_spawn_radius = config->SPAWN_RADIUS;           display_new_val(editorwin,  9, new_spawn_radius);
	int new_initial_predators = config->INITIAL_PREDATORS; display_new_val(editorwin, 10, new_initial_predators);
	int new_initial_prey = config->INITIAL_PREY;           display_new_val(editorwin, 11, new_initial_prey);

	wrefresh(editorwin);


	// makes it so we can use arrow keys
	keypad(editorwin, true);

	std::string choices[13] = {
		"TIMESTEPS",
		"MAX_POPULATION",
		"MAX_DEATHS",
		"MIN_DEATH_AGE",
		"MAX_DEATH_AGE",
		"MAX_HUNGER",
		"BREEDING_DISTANCE",
		"MUNCHING_DISTANCE",
		"PREGNANCY_PERIOD",
		"SPAWN_RADIUS",
		"INITIAL_PREDATORS",
		"INITIAL_PREY",
		"Save and exit"
	};

	bool editing = true;
	while (editing)
	{

		int key_press;
		int highlight = 0;

		// loop for highlighting the menu option
		while (true)
		{
			for (int i = 0; i < 13; i++)
			{

				if (i == highlight)
				{
					wattron(editorwin, A_REVERSE);
				}
				mvwprintw(editorwin, i+3, 40, choices[i].c_str());
				wattroff(editorwin, A_REVERSE);

			}

			key_press = wgetch(editorwin);

			switch(key_press)
			{
				case KEY_UP:
					highlight--;
					if (highlight == -1)
					{
						highlight = 0;
					}
					break;
				case KEY_DOWN:
					highlight++;
					if (highlight == 13)
					{
						highlight = 12;
					}
					break;
				default:
					break;
			}

			if (key_press == 10)
			{
				// option is selected
				switch (highlight)
				{
					case 0:
						new_timesteps = get_new_val(editorwin, 0);
						display_new_val(editorwin, 0, new_timesteps);
						break;
					case 1:
						new_max_population = get_new_val(editorwin, 1);
						display_new_val(editorwin, 1, new_max_population);
						break;
					case 2:
						new_max_deaths = get_new_val(editorwin, 2);
						display_new_val(editorwin, 2, new_max_deaths);
						break;
					case 3:
						new_min_death_age = get_new_val(editorwin, 3);
						display_new_val(editorwin, 3, new_min_death_age);
						break;
					case 4:
						new_max_death_age = get_new_val(editorwin, 4);
						display_new_val(editorwin, 4, new_max_death_age);
						break;
					case 5:
						new_max_hunger = get_new_val(editorwin, 5);
						display_new_val(editorwin, 5, new_max_hunger);
						break;
					case 6:
						new_breeding_distance = get_new_val(editorwin, 6);
						display_new_val(editorwin, 6, new_breeding_distance);
						break;
					case 7:
						new_munching_distance = get_new_val(editorwin, 7);
						display_new_val(editorwin, 7, new_munching_distance);
						break;
					case 8:
						new_pregnancy_period = get_new_val(editorwin, 8);
						display_new_val(editorwin, 8, new_pregnancy_period);
						break;
					case 9:
						new_spawn_radius = get_new_val(editorwin, 9);
						display_new_val(editorwin, 9, new_spawn_radius);
						break;
					case 10:
						new_initial_predators = get_new_val(editorwin, 10);
						display_new_val(editorwin, 10, new_initial_predators);
						break;
					case 11:
						new_initial_prey = get_new_val(editorwin, 11);
						display_new_val(editorwin, 11, new_initial_prey);
						break;
					case 12:
						// confirm new config values
						// write new config values to config.dat
						editing = false;
						break;
					default:
						break;
				}
				break;
			}


		}

	}

	delwin(editorwin);
	clear();
	delete config;
}






int display_menu(int y_max, int x_max)
{
	// create window for out input
	WINDOW *menuwin = newwin(6, x_max-12, y_max-8, 5);
	box(menuwin, 0, 0);
	refresh();
	wrefresh(menuwin);

	// makes it so we can use arrow keys
	keypad(menuwin, true);

	std::string choices[3] = {"Run simulation", "Edit params"};
	int choice;
	int highlight = 0;

	// loop for highlighting the menu option
	while (true)
	{
		for (int i = 0; i < 2; i++)
		{
			if (i == highlight)
			{
				wattron(menuwin, A_REVERSE);
			}
			mvwprintw(menuwin, i+1, 1, choices[i].c_str());
			wattroff(menuwin, A_REVERSE);
		}
		choice = wgetch(menuwin);

		switch(choice)
		{
			case KEY_UP:
				highlight--;
				if (highlight == -1)
				{
					highlight = 0;
				}
				break;
			case KEY_DOWN:
				highlight++;
				if (highlight == 2)
				{
					highlight = 1;
				}
				break;
			default:
				break;
		}
		if (choice == 10)
		{
			break;
		}
	}

	delwin(menuwin);
	clear();
	return highlight;

}









void display_simulation()
{
}


