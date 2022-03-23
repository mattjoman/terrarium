#include <iostream>
#include <ncurses.h>
using namespace std;


void run_simulation(int highlight, int y_max, int x_max);

int display_menu(int y_max, int x_max);

void display_simulation();


int get_new_val(WINDOW* editorwin);

void display_new_val(WINDOW* editorwin, int position, int new_val);

void edit_params(int y_max, int x_max);
