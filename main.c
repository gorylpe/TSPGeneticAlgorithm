#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"
#include "genetic.h"
#include "startingsolution.h"

void mainProgram(FILE* input, FILE* output, FILE* error){
    int n;
    fscanf(input, "%d", &n);

    //save memory
    float** E;
    E = malloc(n * sizeof(float*));
    for (int i = n - 1; i >= 0; --i) {
        E[i] = malloc((i + 1) * sizeof(float));
    }
    initializeEdges(n, E, input);

    int timeLimit;
    fscanf(input, "%d", &timeLimit);
    timeLimit *= CLOCKS_PER_SEC;
    //time for end app and i/o
    timeLimit -= CLOCKS_PER_SEC * n / 10000;

    //forced to be even
    int populationSize = POPULATION_SIZE % 2 == 0 ? POPULATION_SIZE : POPULATION_SIZE + 1;

    int** population = malloc(populationSize * sizeof(int*));
    double* populationLength = malloc(populationSize * sizeof(double));
    firstPopulation(n, population, populationSize, populationLength, E);

    genetic(n, E, population, populationSize, populationLength, timeLimit);

    fprintf(output, "%f\n", *cycleLength);
    int start;
    for (start = 0; start < n && cycle[start] != 0; ++start);
    for (int i = 0; i < n; ++i) {
        fprintf(error, "%d\n", cycle[(start + i)%n] + 1);
    }
    fprintf(error, "%d\n", cycle[start] + 1);

    for (int i = 0; i < n; ++i) {
        free(E[i]);
    }
    free(E);
    free(cycle);
    free(cycleLength);
}

int main(int argc, char* argv[]) {
    FILE* input = stdin;
    FILE* output = stdout;
    FILE* error = stderr;

    srand(time(NULL));

    if(argc > 1)
        input = fopen(argv[1], "r");

    mainProgram(input, output, error);
    //testFirstTemp(input, output, error);

    if(argc > 1)
        fclose(input);
    return 0;
}