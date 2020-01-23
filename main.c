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

//#define ROWLEN 1024
//#define MSIZE [ROWLEN][ROWLEN]

/*void mm(double a[ROWLEN][ROWLEN], double b[ROWLEN][ROWLEN], double c[ROWLEN][ROWLEN]);
void dgemm();
void dgemm_intrins();*/


int main(int argc, char *argv[]) {
    // seed random generator
    srand(2020);
    
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    
    /*double a[ROWLEN][ROWLEN];
     double b[ROWLEN][ROWLEN];
     double c[ROWLEN][ROWLEN];*/
    
    double* a;
    double* b;
    double* c;
    
    a = malloc(ROWLEN*ROWLEN* sizeof(double));
    b = malloc(ROWLEN*ROWLEN* sizeof(double));
    c = malloc(ROWLEN*ROWLEN* sizeof(double));
    
    
    /* initialize matricies */
    
    for(int i=0; i< ROWLEN; i++) {
        for(int j=0; j< ROWLEN; j++) {
            *(a+i+j*ROWLEN) = (double) rand()/UINT_MAX;
            *(b+i+j*ROWLEN) = (double) rand()/UINT_MAX;
            *(c+i+j*ROWLEN) = 0;
        }
    }
    
    
    /*mm(a, b, c);*/
    dgemm(ROWLEN, a, b, c);
    //dgemm_intrins();
    
    end = clock();
    cpu_time_used = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("the elapsed CPU time is %lf\n", cpu_time_used);
    printf("Clocks per sec: %d\n", CLOCKS_PER_SEC);
    
    for (int i = 0; i <  10; i++) {
        for (int j = 0; j < 1; j++) {
            printf("c[%d][%d] = %lf\n", i,j, c[i+j*ROWLEN] );
        }
    }
    return 0;
}






