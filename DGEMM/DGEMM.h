//
//  DGEMM_cacheBLOCKED.h
//  DGEMM_CACHEblocked
//
//  Created by Steven Moody on 4/11/20.
//  Copyright © 2020 Steven Moody. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <x86intrin.h>
#define UNROLL (4)
#ifndef DGEMM_cacheBLOCKED_h
#define DGEMM_cacheBLOCKED_h

#define ROWLEN 4096
#define MSIZE [ROWLEN][ROWLEN]
#define BLOCKSIZE 32


//declaring pointer variables
double* a;
double* b;
double* c;



//function to initialize matricies
void ge(int n, double* a, double* b, double* c);

//function to multiply matricies
void mm(double a[ROWLEN][ROWLEN], double b[ROWLEN][ROWLEN], double c[ROWLEN][ROWLEN]);

//SIMD DGEMM
void dgemm_SIMD (int n, double* a, double* b, double* c);

//first DGEMM
void dgemmOld (int n, double* a, double* b, double* c);

//Pipelined DGEMNM
void dgemmPipelined (int n, double* a, double* b, double* c);

//function to display output
void output(int n, double* a, double* b, double* c);

//New do_block
void do_block (int n, int si, int sj, int sk, double *A, double*B, double *C);

//do_block for parellel
void do_block_Parallel (int n, int si, int sj, int sk, double *A, double *B, double *C);

//Parallel DGEMM
void dgemm_PAR (int n, double* A, double* B, double* C);

//blockcached DGEMM
void dgemm_CACHEBlocked(int n, double* A, double* B, double* C);
#endif /* DGEMM_cacheBLOCKED_h */
