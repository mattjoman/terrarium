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

	int option;

	bool terrarium = true;
	while (terrarium)
	{

		option = display_menu();

		// process option
		switch (option)
		{
			case 0:
				// destroy the window and call the run_simulation function
				run_simulation(option);
				break;
			case 1:
				edit_params();
				break;
			case 2:
				terrarium = false;
				break;
			default:
				refresh();
				break;
		}
	}
	endwin();
	return 0;
}
