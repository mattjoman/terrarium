#pragma once
#include "../share/includes.h"


class Animal
{
	public:
		std::string type;
		int id;
		int age;
		int preg_status;
		std::vector<float> pos;
		std::vector<float> vel;
		int hunger;
		int death_age;

		Animal(int id, std::vector<float> pos, int min_death_age, int max_death_age);
		void move();
		void print_pos();
		bool is_pregnant(); //
		bool is_due(); //
		void conceive(int pregnancy_period); //
		void continue_pregnancy(); //
		bool is_hungry();
		void eat(); //
		virtual void inc_hunger();
		void inc_age(); //
		virtual void print();
		void update(); //
		virtual ~Animal();
};
