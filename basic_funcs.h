/*
 *	General functions that do not use objects
 *	specific to this project.
 *	Mostly functions involving vector calculations.
 */
#pragma once

float rand_float(int from, int to, int seed);

std::vector<float> rand_direction();

std::vector<float> rand_vector(int from, int to);

std::vector<float> vector_difference(std::vector<float> v1, std::vector<float> v2);

float scalar_difference(std::vector<float> v1, std::vector<float> v2);

