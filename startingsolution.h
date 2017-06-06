#pragma once
#include <string.h>
#include "util.h"
#include "swap2opt.h"

void firstCycleAscending(int n, int* cycle);

void firstCycleRandom(int n, int* cycle);

void firstCycleNearestNeighbor(int n, int *cycle, float **E);

void firstCycleNearestInsertion(int n, int *cycle, float **E);

void firstPopulationPredef(int n, int **population, int populationSize, double *populationLength, float **E);

void firstPopulation1nnRestRandom(int n, int **population, int populationSize, double *populationLength, float **E);