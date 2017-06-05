#include "genetic.h"
#define DEBUG

inline int countNeighbors(bool freeVertices[], int neighbors[][4], int v){
    int neighborsNumber = 0;
    for(int i = 0; i < 4; ++i){
        if(freeVertices[neighbors[v][i]])
            ++neighborsNumber;
    }
    return neighborsNumber;
}

void singleEdgeCrossover(int n, int** population, int populationFrom1, int populationFrom2, int populationTo){
    bool freeVertices[n];
    for(int i = 0; i < n; ++i){
        freeVertices[i] = true;
    }
    int freeVerticesArr[n];
    int usedVertices = 0;
    //choose random vertex from vertices between <it,n), put vertex at it position and increase it
    firstCycleAscending(n, freeVerticesArr);

    //create neighborhood of every vertex
    int neighbors[n][4];
    int v, vl, vr;
    for(int i = 0; i < n; ++i){
        v = population[populationFrom1][i];
        vl = i > 0 ? population[populationFrom1][i - 1] : population[populationFrom1][n - 1];
        vr = i < n - 1 ? population[populationFrom1][i + 1] : population[populationFrom1][0];

        neighbors[v][0] = vl;
        neighbors[v][1] = vr;

        v = population[populationFrom2][i];
        vl = i > 0 ? population[populationFrom2][i - 1] : population[populationFrom2][n - 1];
        vr = i < n - 1 ? population[populationFrom2][i + 1] : population[populationFrom2][0];

        neighbors[v][2] = vl;
        neighbors[v][3] = vr;
    }

    //choose vertex from free vertices
    int vi = rand() % (n - usedVertices) + usedVertices;
    v = freeVerticesArr[vi];
    population[populationTo][usedVertices] = v;
    //remove from free vertices array
    swap(&freeVerticesArr[vi], &freeVerticesArr[usedVertices]);
    ++usedVertices;


    while(usedVertices < n){
        int neighborsNumber = countNeighbors(freeVertices, neighbors, v);

        if(neighborsNumber == 0){
            //choose vertex from free vertices
            vi = rand() % (n - usedVertices) + usedVertices;
            v = freeVerticesArr[vi];
            population[populationTo][usedVertices] = v;
            //remove from free vertices array
            swap(&freeVerticesArr[vi], &freeVerticesArr[usedVertices]);
            ++usedVertices;
        } else {
            //choose neighbor with minimal number of neighbors
            int minNeighborsVerticeIt = -1;
            int minNeighborsVerticeSize = INT_MAX;
            for(int i = 0; i < 4; ++i){
                if(freeVertices[neighbors[v][i]]){
                    neighborsNumber = countNeighbors(freeVertices, neighbors, neighbors[v][i]);
                    if(neighborsNumber < minNeighborsVerticeSize){
                        minNeighborsVerticeSize = neighborsNumber;
                        minNeighborsVerticeIt = i;
                    }
                }
            }

            //append vertex to child
            v = neighbors[v][minNeighborsVerticeIt];
            population[populationTo][usedVertices] = v;
            //find it in free vertices array
            for(int i = usedVertices; i < n; ++i){
                if(freeVerticesArr[i] == v){
                    vi = i;
                    break;
                }
            }
            //remove from free vertices array
            swap(&freeVerticesArr[vi], &freeVerticesArr[usedVertices]);
            ++usedVertices;
        }
    }

}

void edgeCrossover(int n, int** population, const int populationSize){
    const int populationSizeHalf = populationSize / 2;
    singleEdgeCrossover(n, population, n - 1, 0, populationSizeHalf);
    for(int i = 1; i < populationSizeHalf; ++i){
        singleEdgeCrossover(n, population, i - 1, i, populationSizeHalf + i);
    }
}

//p/q chances to do single mutation, ie. 1/2 means 50%
void randomMutations(int n, int** population, const int populationSize, int p, int q){
    const int populationSizeHalf = populationSize / 2;

    for(int i = populationSizeHalf; i < populationSize; ++i){
        if(rand() % q < p){
            //random mutation
            int b = rand() % (n - 2) + 1;
            int a = rand() % b;
            int al = a > 0 ? a - 1 : n - 1;
            int ar = a < n - 1 ? a + 1 : 0;
            int bl = b > 0 ? b - 1 : n - 1;
            int br = b < n - 1 ? b + 1 : 0;

            swap2Opt(n, population[i], a, b);
        }
    }
}

void measurePopulationLengths(int n, float** E, int **population, int populationSize, double *populationLength) {
    for(int i = 0; i < populationSize; ++i){
        populationLength[i] = cycleLen(n, population[i], E);
    }
}

int genetic(int n, float **E, int** population, int populationSize, double* populationLength, int timeLimit){

    while(clock() < timeLimit){
        edgeCrossover(n, population, populationSize);
        randomMutations(n, population, populationSize, 1, 2);
        measurePopulationLengths(n, E, population, populationSize, populationLength);
        sortPopulation(n, population, populationSize, populationLength);
    }
#ifdef DEBUG
    printf("\n");
    printf("%d %d\n", timeLimit, clock());
#endif
}
