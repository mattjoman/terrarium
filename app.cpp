#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <ncurses.h>
#include "simulation.h"
#include "config.h"
#include "app.h"
using namespace std;



void run_simulation(int highlight)
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
	
	// create window for displaying simulation progress
	int y_max, x_max;
	getmaxyx(stdscr, y_max, x_max);
	int n_lines  =  7;
	int n_cols   = 70;
	int begin_y  =  1;
	int begin_x  =  1;
	WINDOW *simwin = newwin(n_lines, n_cols, begin_y, begin_x);
	//WINDOW *simwin = newwin(6, x_max-12, y_max-8, 5);
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
	WINDOW *reviewwin = newwin(n_lines, n_cols, begin_y, begin_x);
	//WINDOW *reviewwin = newwin(7, x_max-12, y_max-8, 5);
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
}











int get_new_val(WINDOW* editorwin)
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
		mvwprintw(editorwin, position + 3, i + 56, " ");
	}
	mvwprintw(editorwin, position + 3, 56, "%d", new_val);
	wrefresh(editorwin);
}








void edit_params()
{
	int y_max, x_max;
	getmaxyx(stdscr, y_max, x_max);
	int n_lines  = 18;
	int n_cols   = 70;
	int begin_y  =  1;
	int begin_x  =  1;
	WINDOW *editorwin = newwin(n_lines, n_cols, begin_y, begin_x);
	box(editorwin, 0, 0);
	refresh();
	wrefresh(editorwin);

	// read the config file
	//Config* config = read_config();
	std::map<std::string, int> config = read_config();
	
	// make map for new config:
	std::map<std::string, int> new_config = {};



	// display the current config values (new way)
	mvwprintw(editorwin, 1,  1, "Current config:");
	mvwprintw(editorwin, 1, 36, "New config:");
	int i = 0;
	for (auto itr = config.begin(); itr != config.end(); itr++)
	{
		// copy the old config into the new config
		new_config[(*itr).first] = (*itr).second;

		// display key value pair
		mvwprintw(editorwin, i+3, 1, "%s", (*itr).first.c_str());
		mvwprintw(editorwin, i+3, 21, "%d", (*itr).second);

		// display the new config
		mvwprintw(editorwin, i+3, 36, "%s", (*itr).first.c_str());
		mvwprintw(editorwin, i+3, 56, "%d", new_config[(*itr).first]);

		i++;
	}
	wrefresh(editorwin);

	// makes it so we can use arrow keys
	keypad(editorwin, true);

	std::string choices[13] = {
		"BREEDING_DISTANCE",
		"INITIAL_PREDATORS",
		"INITIAL_PREY",
		"MAX_DEATHS",
		"MAX_DEATH_AGE",
		"MAX_HUNGER",
		"MAX_POPULATION",
		"MIN_DEATH_AGE",
		"MUNCHING_DISTANCE",
		"PREGNANCY_PERIOD",
		"SPAWN_RADIUS",
		"TIMESTEPS",
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
				mvwprintw(editorwin, i+3, 36, choices[i].c_str());
				wattroff(editorwin, A_REVERSE);
			}

			key_press = wgetch(editorwin);

			if (key_press == KEY_UP && highlight > 0)
			{
				highlight--;
			}
			else if (key_press == KEY_DOWN && highlight < 12)
			{
				highlight++;
			}
			else if (key_press == 10 && highlight < 12)
			{
				int new_val = get_new_val(editorwin);
				new_config[choices[highlight]] = new_val;
				display_new_val(editorwin, highlight, new_val);
				break;
			}
			else if (key_press == 10 && highlight == 12)
			{
				editing = false;
				break;
			}
		}
	}
	write_config(new_config);
	delwin(editorwin);
	clear();
}






int display_menu()
{
	// create window for out input
	int y_max, x_max;
	getmaxyx(stdscr, y_max, x_max);
	int n_lines  =  6;
	int n_cols   = 60;
	int begin_y  =  1;
	int begin_x  =  1;
	WINDOW *menuwin = newwin(n_lines, n_cols, begin_y, begin_x);
	box(menuwin, 0, 0);
	refresh();
	wrefresh(menuwin);

	// makes it so we can use arrow keys
	keypad(menuwin, true);

	std::string choices[3] = {"Run simulation", "Edit params", "Quit"};
	int choice;
	int highlight = 0;

	// loop for highlighting the menu option
	while (true)
	{
		for (int i = 0; i < 3; i++)
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
				if (highlight == 3)
				{
					highlight = 2;
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


