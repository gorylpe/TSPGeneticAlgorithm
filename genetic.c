#include "genetic.h"
#define DEBUG

int genetic(int n, float **E, int** population, double** populationLength, int timeLimit){
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