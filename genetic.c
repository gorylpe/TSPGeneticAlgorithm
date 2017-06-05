#include "genetic.h"
#define DEBUG

void singleEdgeCrossover(int n, int** population, int populationSize, double* populationLength, int populationFrom1, int populationFrom2, int populationTo){

}

void edgeCrossover(int n, int** population, int populationSize, double* populationLength){

}

int genetic(int n, float **E, int** population, int populationSize, double* populationLength, int timeLimit){
    int* tmpCycle = malloc(n * sizeof(int));
    int* tmpCycleSecondary = malloc(n * sizeof(int));
    double tmpLength = *bestCycleLength;
    memcpy(tmpCycle, bestCycle, n * sizeof(int));


    while(clock() < timeLimit){

    }
#ifdef DEBUG
    printf("\n");
    printf("%d %d\n", timeLimit, clock());
#endif
}