#pragma once
#include "includes.h"


struct Animal
{
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
	bool is_pregnant(); //
	bool is_due(); //
	void conceive(); //
	void continue_pregnancy(); //
	bool is_hungry();
	void eat(); //
	virtual void inc_hunger();
	void inc_age(); //
	virtual void print();
	void update(); //
	virtual ~Animal();
};
