#include "swap2opt.h"

void swap2Opt(int n, int* cycle, int a, int b) {
    int length = b - a;

#ifdef DEBUG
    if(a > b)
        printf("swap2opt a > b");
#endif

    const int end = length / 2;
    for(int i = 0; i < end; ++i){
        swap(&cycle[a + i], &cycle[b - i]);
    }
}
