#include <iostream>
#include <ncurses.h>
using namespace std;


void run_simulation(int highlight);

int display_menu();

void display_simulation();


int get_new_val(WINDOW* editorwin);

void display_new_val(WINDOW* editorwin, int position, int new_val);

void edit_params();
