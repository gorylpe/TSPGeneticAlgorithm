#include "genetic.h"
//#define DEBUG

static inline int countNeighbors(bool freeVertices[], int neighbors[][4], int v){
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

void edgeCrossoverOneWithNext(int n, int **population, const int populationSize){
    const int populationSizeHalf = populationSize / 2;
    singleEdgeCrossover(n, population, n - 1, 0, populationSizeHalf);
    for(int i = 1; i < populationSizeHalf; ++i){
        singleEdgeCrossover(n, population, i - 1, i, populationSizeHalf + i);
    }
}

void edgeCrossoverEliteMost(int n, int **population, const int populationSize){
    const int populationSizeForty = populationSize / 10 * 4;
    for(int i = 0; i < 10; ++i){
        singleEdgeCrossover(n, population, 0, i + 1, populationSizeForty + i);
    }

    for(int i = 0; i < 10; ++i){
        singleEdgeCrossover(n, population, 1, i + 2, populationSizeForty + 10 + i);
    }

    for(int i = 0; i < 10; ++i){
        singleEdgeCrossover(n, population, 2, i + 3, populationSizeForty + 20 + i);
    }

    for(int i = 0; i < 3; ++i){
        singleEdgeCrossover(n, population, 3, i + 4, populationSizeForty + 30 + i);
    }

    for(int i = 0; i < 2; ++i){
        singleEdgeCrossover(n, population, 4, i + 5, populationSizeForty + 33 + i);
    }

    for(int i = 0; i < 25; ++i){
        singleEdgeCrossover(n, population, 5 + i, 5 + i + 1, populationSizeForty + 35 + i);
    }
}

//p/q chances to do single mutation, ie. 1/2 means 50%
void randomMutations(int n, int** population, const int populationSize, int p, int q){
    const int populationSizeQuarter = populationSize / 4;

    for(int i = populationSizeQuarter; i < populationSize; ++i){
        if(rand() % q < p){
            //random mutation
            int b = rand() % (n - 2) + 1;
            int a = rand() % b;
            swap2Opt(n, population[i], a, b);
        }
    }
}

void measurePopulationLengths(int n, float** E, int **population, const int populationSize, double *populationLength) {
    for(int i = 0; i < populationSize; ++i){
        populationLength[i] = cycleLen(n, population[i], E);
    }
}

int partition(int left, int right, int** population, double* populationLength) {
    double pivot = populationLength[left];

    int i = left - 1;
    int j = right + 1;

    while(true){
        do{
            ++i;
        } while(populationLength[i] < pivot);

        do{
            --j;
        } while(populationLength[j] > pivot);

        if(i >= j)
            return j;

        swapD(&populationLength[i], &populationLength[j]);
        swapArr(&population[i], &population[j]);
    }
}

void quicksortPopulation(int left, int right, int **population, double *populationLength){
    while(right > left){
        int mid = partition(left, right, population, populationLength);

        if((mid - left) < (right - mid)){
            quicksortPopulation(left, mid - 1, population, populationLength);
            left = mid + 1;
        } else {
            quicksortPopulation(mid + 1, right, population, populationLength);
            right = mid - 1;
        }
    }
}

int genetic(int n, float **E, int** population, const int populationSize, double* populationLength, int timeLimit){
#ifdef DEBUG
    printf("Start");
#endif
    int maxGenerations = 5000;
    int generation = 0;
    while(clock() < timeLimit && generation < maxGenerations){
        edgeCrossoverEliteMost(n, population, populationSize);
        randomMutations(n, population, populationSize, 1, 1);
        measurePopulationLengths(n, E, population, populationSize, populationLength);
        quicksortPopulation(0, populationSize - 1, population, populationLength);

#ifdef DEBUG
        printf("Best cycle length:%lf\n", populationLength[0]);
        double avg = 0.0;
        for(int i = 0; i < populationSize; ++i){
            avg += populationLength[i];
        }
        avg /= populationSize;
        printf("Average cycle length:%lf\n", avg);
        avg = 0.0;
        for(int i = 0; i < populationSize / 2; ++i){
            avg += populationLength[i];
        }
        avg /= populationSize;
        printf("Average of half cycle length:%lf\n", avg);
        printf("\n");
#endif
        ++generation;
        double avg = 0.0;
        for(int i = 0; i < populationSize; ++i){
            avg += populationLength[i];
        }
        avg /= populationSize;
        printf("%lf, ", avg);
    }
#ifdef DEBUG
    printf("\n");
    printf("%d %d\n", timeLimit, clock());
#endif
}
