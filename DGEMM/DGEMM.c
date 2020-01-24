//
//  DGEMM.c
//  DGEMM
//
//  Created by Steven Moody on 1/23/20.
//  Copyright © 2020 Steven Moody. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "DGEMM.h"



void ge(int n, double* A, double* B, double* C){
    
    for(int i=0; i< ROWLEN; i++) {
        for(int j=0; j< ROWLEN; j++) {
            *(a+i+j*ROWLEN) = (double) rand()/UINT_MAX;
            *(b+i+j*ROWLEN) = (double) rand()/UINT_MAX;
            *(c+i+j*ROWLEN) = 0;
        }
    }
}

void mm(double a[ROWLEN][ROWLEN], double b[ROWLEN][ROWLEN], double c[ROWLEN][ROWLEN]) {
    
    int i,j,k;
    for (i = 0; i != ROWLEN; i++) {
        for (j = 0; j != ROWLEN; j++) {
            for (k = 0; k != ROWLEN; k++) {
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }
        }
    }
}

void dgemm (int n, double* A, double* B, double* C){
    
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            double cij = C[i+j*n]; /* cij = C[i][j] */
                for( int k = 0; k < n; k++ )
                    cij += A[i+k*n] * B[k+j*n]; /* cij += A[i][k]*B[k][j] */
                    C[i+j*n] = cij; /* C[i][j] = cij */
    }
}

void output(int n, double* A, double* B, double* C){
for (int i = 0; i <  10; i++) {
    for (int j = 0; j < 1; j++) {
        printf("c[%d][%d] = %lf\n", i,j, c[i+j*ROWLEN] );
    }
  }
}

void dgemm_intrins() {
}
