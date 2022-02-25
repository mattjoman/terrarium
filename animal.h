#pragma once
#include "includes.h"


struct Animal {
	std::string type;
	int id;
	int age;
	int preg_status;
	std::vector<float> pos;
	std::vector<float> vel;
	int hunger;

	Animal(int id);
	void move();
	void print_pos();
	virtual void print();
	virtual ~Animal();
};
