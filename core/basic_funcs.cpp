/*
 *	General functions that do not use objects
 *	specific to this project.
 *	Mostly functions involving vector calculations.
 */
#include "basic_funcs.h"
#include "../share/includes.h"
#include <cstddef>


int rand_int(int from, int to, int seed)
{
	// return an integer between from and to
	srand(seed);
	int num = from + rand() % (to-from);
	return num;
}


float rand_float(int from, int to, int seed)
{
	// return an integer (converted to float) between from and to
	srand(seed);
	float num = static_cast<float>(from + rand() % (to-from));
	return num;
}


std::vector<float> rand_direction()
{
	// returns vector of unit length and random direction
	std::random_device rd;
	float rad = rand_float(0, 360, rd())*(M_PI/180);
	std::vector<float> direction = {static_cast<float>(cos(rad)), static_cast<float>(-sin(rad))};
	return direction;
}


std::vector<float> rand_vector(int from, int to)
{
	// returns a vector of random magnitude (within specified range) and random direction
	std::vector<float> vec = rand_direction();
	std::random_device rd;
	float magnitude = rand_float(from, to, rd());
	vec[0] *= magnitude;	
	vec[1] *= magnitude;	
	return vec;
}


std::vector<float> vector_difference(std::vector<float> v1, std::vector<float> v2)
{
	// return a vector pointing from v1 to v2
	std::vector<float> diff;
	diff.push_back(v2[0] - v1[0]);
	diff.push_back(v2[1] - v1[1]);
	return diff;
}


float scalar_difference(std::vector<float> v1, std::vector<float> v2)
{
	// return distance from v1 to v2
	float a_sq = pow((v2[0] - v1[0]), 2);
	float b_sq = pow((v2[1] - v1[1]), 2);
	return sqrt(a_sq + b_sq);
}


void sort(int arr[], size_t len)
{
	int tmp;
	int is_sorted;
	while (true) {
		std::cout << "Once through" << std::endl;
		is_sorted = 1;
		for (int i=0; i<len-1; i++) {
			if (arr[i]>arr[i+1]) {
				is_sorted = 0;
				tmp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = tmp;
			}
		}
		if (is_sorted) {
			break;
		}
	}
}


