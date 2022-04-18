#include <iostream>
#include <string>

std::string create_output_path(const char* output_path);

void run_simulation(const char* output_path);

void display_params();

void edit_param(std::string param_name, int new_val);

void print_file(std::string file_path);
