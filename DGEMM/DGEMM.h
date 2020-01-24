//
//  DGEMM.h
//  DGEMM
//
//  Created by Steven Moody on 1/23/20.
//  Copyright © 2020 Steven Moody. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#ifndef DGEMM_h
#define DGEMM_h

#define ROWLEN 1024
#define MSIZE [ROWLEN][ROWLEN]
double* a;
double* b;
double* c;
    void ge(int n, double* a, double* b, double* c);

    void mm(double a[ROWLEN][ROWLEN], double b[ROWLEN][ROWLEN], double c[ROWLEN][ROWLEN]);
    
    void dgemm (int n, double* a, double* b, double* c);

    void output(int n, double* a, double* b, double* c);


#endif /* DGEMM_h */

