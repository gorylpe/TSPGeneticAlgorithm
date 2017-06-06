#pragma once
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "util.h"

void swap2Opt(int n, int* cycle, int a, int b);

//calculate diff in const time
static inline float cycleLen2OptDiff(int* cycle, float** E, int al, int a, int b, int br){
    if(a == b)
        return 0.0;
    if(al == br)
        return 0.0;
    if(al == b)
        return 0.0;
    float diff;
    diff = -(E(cycle[al],cycle[a]) + E(cycle[b],cycle[br]));
    diff += E(cycle[al],cycle[b]) + E(cycle[a],cycle[br]);
    /*printf("(%d;%d) -> (%d;%d)", cycle[al], cycle[a], cycle[b], cycle[br]);
    printf("diff: -%f-%f+%f+%f=%f\n", E(cycle[al],cycle[a]), E(cycle[b],cycle[br]), E(cycle[al],cycle[b]), E(cycle[a],cycle[br]), diff);*/
    return diff;
}