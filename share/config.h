#pragma once

#include <map>
#include <string>

#define ANIMAL_LIST_LENGTH 100000
#define DEATH_LIST_LENGTH  100000

void read_config_global();

std::map<std::string, int> read_config();

void write_config(std::map<std::string, int> new_config);
