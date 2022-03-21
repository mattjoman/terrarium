#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <ncurses.h>
#include "simulation.h"
#include "app.h"
using namespace std;



void run_simulation(int highlight, int y_max, int x_max)
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
		//mvwprintw(reviewwin, 2, 1, "Simulation completed successfully.");
		break;
	case 1:
		mvwprintw(reviewwin, 1, 1, "Exit code 1: Simulation stopped early due to high population.");
		//mvwprintw(reviewwin, 2, 1, "Simulation stopped early due to high population.");
		break;
	case 2:
		mvwprintw(reviewwin, 1, 1, "Exit code 2: Simulation stopped early because everything died.");
		//mvwprintw(reviewwin, 2, 1, "Simulation stopped early because everything died.");
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








void edit_params(int y_max, int x_max)
{
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

	string choices[3] = {"Run simulation", "Edit params"};
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


