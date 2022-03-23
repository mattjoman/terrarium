#include "app.h"
#include "simulation.h"

int main(int argc, char ** argv)
{
	initscr();
	noecho();
	cbreak();
	curs_set(0);

	// get screen size
	int y_max, x_max;
	getmaxyx(stdscr, y_max, x_max);

	int option;

	while (true)
	{

		option = display_menu(y_max, x_max);

		// process option
		switch (option)
		{
			case 0:
				// destroy the window and call the run_simulation function
				run_simulation(option, y_max, x_max);
				break;
			case 1:
				edit_params(y_max, x_max);
				break;
			default:
				refresh();
				break;
		}
	}

	// make sure program waits before exiting
	getch();
	endwin();

	return 0;
}
