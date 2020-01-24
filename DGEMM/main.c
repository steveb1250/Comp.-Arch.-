//
//  main.c
//  DGEMM
//
//  Created by Steven Moody on 1/23/20.
//  Copyright © 2020 Steven Moody. All rights reserved.
//
// thanks to Joshua Skootsky
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "DGEMM.h"



int main(int argc, char *argv[]) {
    // seed random generator
    srand(2020);
    
    double* a;
    double* b;
    double* c;
    
    a = malloc(ROWLEN*ROWLEN* sizeof(double));
    b = malloc(ROWLEN*ROWLEN* sizeof(double));
    c = malloc(ROWLEN*ROWLEN* sizeof(double));
    
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    
    ge(ROWLEN, a, b, c);
    /*mm(a, b, c);*/
    dgemm(ROWLEN, a, b, c);
    //dgemm_intrins();
    
    end = clock();
    cpu_time_used = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("the elapsed CPU time is %lf\n", cpu_time_used);
    printf("Clocks per sec: %d\n", CLOCKS_PER_SEC);
    
    output(ROWLEN, a, b, c);
    
    return 0;
}






