/*
 * Do the random initail positions better.
 * Maybe use floats 'px', 'py', 'vx', 'vy' instead of vectors for positions and velocities?
 * Add iterators (to the indeces of doomed animals) to 'kill_list'. Then send all the iterators to 'erase_animal()' so they can be destroyed and memory can be freed.
 */
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ANIMALS 10000

using namespace std;

float rand_float(int from, int to, int seed) {
	// return an integer (converted to float) between from and to
	srand(seed);
	float num = static_cast<float>(from + rand() % (to-from));
	return num;
}



struct Animal {
	int id;
	vector<float> pos;
	vector<float> vel;
	int hunger;
	Animal(int id_) : id{id_} {
		// make random vectors for pos and vel
		// figure out how to make this constructor run for derived classes
		cout << "id_: " << id << endl;
		int from = -10;
		int to = 10;
		int seed1 = 1*id;
		int seed2 = 2*id;
		pos.push_back(rand_float(from, to, seed1));
		pos.push_back(rand_float(from, to, seed2));
		vel.push_back(1); vel.push_back(-1);
		hunger = 5;
	}
	void move() {
		pos[0] += vel[0];
		pos[1] += vel[1];
	}
	void print_pos() {
		cout << pos[0] << "," << pos[1] << endl;
	}
	virtual void print() {cout << "ANIMAL" << endl;}
};






struct Predator : Animal {
	Predator(int id_) : Animal{id_} {}

	void print() {
		cout << "PREDATOR" << endl;
	}
};

struct Prey : Animal {
	Prey(int id_) : Animal{id_} {}

	void print() {
		cout << "PREY" << endl;
	}
};



void new_animal(int &id, string species, vector<Animal*> &animal_list) {
	string species1("pred");
	string species2("prey");

	if (species.compare(species1) == 0) {

		cout << "New Predator..." << endl;
		Predator* animal = new Predator(id);
		animal_list.push_back(animal);

	} else if (species.compare(species2) == 0) {

		cout << "New Prey..." << endl;
		Prey* animal = new Prey(id);
		animal_list.push_back(animal);

	}
	id++;
}


void erase_animal(vector<Animal*> &animal_list, vector<Animal*>::iterator iter) {
	delete *iter;
	animal_list.erase(iter);
}

void destroy_animal_list(vector<Animal*> &animal_list) {
	// delete all animals in 'animal_list' and clear the vector
	for (vector<Animal*>::iterator it=animal_list.begin(); it!=animal_list.end(); it++) {
		cout << (*it)->id << endl;
		delete *it;
	}
	animal_list.clear();
}


int main() {

	// initialising
	const int timesteps = 100;
	int id = 0;
	int n_predators = 2;
	int n_prey = 4;
	vector<Animal*>::iterator kill_list[MAX_ANIMALS];
	vector<Animal*> animal_list;

	// declare an iterator variable
	vector<Animal*>::iterator iter;

	// better way of doing this?
	string label1("pred");
	string label2("prey");

	// make initial predators and prey
	for (int i=0; i<n_predators; i++) {
		new_animal(id, label1, animal_list);
	}
	for (int i=0; i<n_prey; i++) {
		new_animal(id, label2, animal_list);
	}
	

	// testing the kill_list iterator technique
	iter = animal_list.begin();
	kill_list[0] = iter;
	cout << "something: " << (*kill_list[0])->id << endl;
	delete *kill_list[0];
	animal_list.erase(kill_list[0]);



	// main simulation loop
	for (int t=0; t<timesteps; t++) {
		for (int a=0; a<animal_list.size(); a++) {
			animal_list[a]->move();
		}
	}





	// delete the 4th animal in 'animal_list'
	iter = animal_list.begin() + 3;
	erase_animal(animal_list, iter);
	
	// cleaning up
	destroy_animal_list(animal_list);	

	return 0;
}

