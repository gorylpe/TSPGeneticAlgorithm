#include "startingsolution.h"

void firstCycleAscending(int n, int* cycle) {
    for (int i = 0; i < n; ++i) {
        cycle[i] = i;
    }
}

void permuteCycle(int n, int* cycle){
    for(int i = n - 1; i >= 0; --i){
        int j = rand()%(i + 1);
        swap(&cycle[i], &cycle[j]);
    }
}

void firstCycleRandom(int n, int* cycle) {
    firstCycleAscending(n, cycle);
    permuteCycle(n, cycle);
}


void firstCycleNearestNeighbor(int n, int *cycle, float **E) {
    firstCycleAscending(n, cycle);
    int max = n - 1;
    for (int i = 0; i < max; ++i) {
        int minIt = i + 1;
        double min = E(cycle[i],cycle[minIt]);
        for (int j = minIt + 1; j < n; ++j) {
            if (E(cycle[i],cycle[j]) < min) {
                minIt = j;
                min = E(cycle[i],cycle[j]);
            }
        }
        swap(&cycle[i + 1], &cycle[minIt]);
    }
}

void firstCycleNearestInsertion(int n, int *cycle, float **E) {
    firstCycleAscending(n, cycle);
    double len = E(0,1) + E(1,0);
    for (int i = 2; i < n; ++i) {
        int insertIt = i; //dla kolejnych i, cycle[i] = i
        double minLen = len - E(cycle[insertIt - 1],0) + E(cycle[i - 1],cycle[i]) + E(i,0); //cycle[insertIt % i] = 0 because last element of cycle is 0th;
        for (int j = insertIt - 1; j >= 1; --j) {
            double tmpLen = len - E(cycle[j - 1],cycle[j]) + E(cycle[j - 1],cycle[i]) + E(cycle[i],cycle[j]);
            if (tmpLen < minLen) {
                minLen = tmpLen;
                insertIt = j;
            }
        }
        if (insertIt < i) {
            memmove(&cycle[insertIt + 1], &cycle[insertIt], (i - insertIt) * sizeof(int));
            cycle[insertIt] = i;
        }
        len = minLen;
    }
}

void firstPopulation(int n, int** population, int populationSize, double* populationLength, float** E){
    int* cycle = malloc(n * sizeof(int));
    firstCycleNearestInsertion(n, cycle, E);
    population[0] = cycle;
    cycle = malloc(n * sizeof(int));
    firstCycleNearestNeighbor(n, cycle, E);
    population[1] = cycle;
    for(int i = 2; i < populationSize; ++i){
        cycle = malloc(n * sizeof(int));
        if(i % 2 == 0)
            firstCycleNearestNeighbor(n, cycle, E);
        else
            firstCycleNearestInsertion(n, cycle, E);

        //number of mutations
        int k = rand() % 10;
        for(int j = 0; j < k; ++j){
            //random mutation
            int b = rand() % (n - 1) + 1;
            int a = rand() % b;
            swap(&cycle[a], &cycle[b]);
        }
    }
    for(int i = 0; i < populationSize; ++i){
        populationLength[i] = cycleLen(n, population[i], E);
    }
}