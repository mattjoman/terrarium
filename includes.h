#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <stdio.h>
#include <stdlib.h>

#define TIMESTEPS 150 // maximum number of timesteps
#define MAX_DEATHS 10000 // maximum deaths per timestep
#define MAX_AGE 20 // maximum age of animals
#define MAX_HUNGER 20 // maximum hunger for animals
#define BREEDING_DISTANCE 2 // max distance animals can breed across
#define MUNCHING_DISTANCE 2 // max distance at which predators can eat prey
#define PREGNANCY_PERIOD 3 // defines time between breeding and birth
#define SPAWN_RADIUS 10 // animals spawn within this radius of their birth-location
#define INITIAL_PREDATORS 7 // initial predator count
#define INITIAL_PREY 7 // initial prey count
#define FOV 10 // max distance animals can see
