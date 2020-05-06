//
//  main.c
//  DGEMM_CACHEblocked
//
//  Created by Steven Moody on 4/11/20.
//  Copyright © 2020 Steven Moody. All rights reserved.
//


#include "DGEMM_cacheBLOCKED.h"

int main(int argc, char *argv[]) {
    // seed random generator
    srand(2020);
    
    
    //initialize malloc for variables
    a = malloc(ROWLEN*ROWLEN* sizeof(double));
    b = malloc(ROWLEN*ROWLEN* sizeof(double));
    c = malloc(ROWLEN*ROWLEN* sizeof(double));

//=========================================================================================================
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    
    //run initialize and multiplying functions
    ge(ROWLEN, a, b, c);
    
    dgemmOld(ROWLEN, a, b, c);
    
    //dgemm_intrins();
    
    //End clock on Plain
    end = clock();
    cpu_time_used = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("the elapsed CPU time for plain DGEMM is %lf\n", cpu_time_used);
    printf("Clocks per sec: %d\n", CLOCKS_PER_SEC);
    
    //run output function
    output(ROWLEN, a, b, c);
    
    
    
    
    
//=========================================================================================================
    //Start clock for SIMD
    clock_t startSIMD, endSIMD;
    double cpu_time_usedSIMD;
    startSIMD = clock();
    
    
    //Run DGEMM SIMD
    dgemm_SIMD(ROWLEN, a, b, c);
    
    //End clock for SIMD
    endSIMD = clock();
    cpu_time_usedSIMD = ((double)(endSIMD - startSIMD))/CLOCKS_PER_SEC;
    printf("\n\nthe elapsed CPU time for SIMD is %lf\n", cpu_time_usedSIMD);
    printf("Clocks per sec: %d\n", CLOCKS_PER_SEC);
    
    //run output function
    output(ROWLEN, a, b, c);
    
    
    
    
//=========================================================================================================
    //Start clock from pipelined
    clock_t startPipelined, endPipelined;
    double cpu_time_usedPipelined;
    startPipelined = clock();
    
    
    //Run DGEMM Pipelined
    dgemmPipelined(ROWLEN, a, b, c);
    
    //End clock for Pipelined
    endPipelined = clock();
    cpu_time_usedPipelined = ((double)(endPipelined - startPipelined))/CLOCKS_PER_SEC;
    printf("\n\nthe elapsed CPU time for the pipelined version is  is %lf\n", cpu_time_usedPipelined);
    printf("Clocks per sec: %d\n", CLOCKS_PER_SEC);
    
    //run output function
    output(ROWLEN, a, b, c);
    
//==========================================================================================================
    //Start clock for CACHBlocked
    clock_t startCACHEBlocked, endCACHEBlocked;
    double cpu_time_usedCACHEBlocked;
    startCACHEBlocked = clock();

    //run DGEMM_CACHEBlocked
    dgemm_CACHEBlocked(ROWLEN, a, b, c);
    
    //End clock for CACHE_Blocked
    endCACHEBlocked = clock();
    cpu_time_usedCACHEBlocked = ((double)(endCACHEBlocked - startCACHEBlocked))/CLOCKS_PER_SEC;
    printf("\n\nthe elapsed CPU time for the CACHEBlocked version is  is %lf\n", cpu_time_usedCACHEBlocked);
    printf("Clocks per sec: %d\n", CLOCKS_PER_SEC);
    
    output(ROWLEN, a, b, c);
//===========================================================================================================
    //Start clock for Parallel
    clock_t startParallel, endParallel;
    double cpu_time_usedParallel;
    startParallel = clock();
    
    //run DGEMM_CACHEBlocked
    dgemm_PAR(ROWLEN, a, b, c);
    
    //End clock for CACHE_Blocked
    endParallel = clock();
    cpu_time_usedParallel = ((double)(endParallel - startParallel))/CLOCKS_PER_SEC;
    printf("\n\nthe elapsed CPU time for the Parallel version is  is %lf\n", cpu_time_usedParallel);
    printf("Clocks per sec: %d\n", CLOCKS_PER_SEC);
    
    output(ROWLEN, a, b, c);
    return 0;
}

