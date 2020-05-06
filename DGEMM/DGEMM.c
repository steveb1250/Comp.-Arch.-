//
//  DGEMM_cacheBLOCKED.c
//  DGEMM_CACHEblocked
//
//  Created by Steven Moody on 4/11/20.
//  Copyright © 2020 Steven Moody. All rights reserved.
//

#include "DGEMM_cacheBLOCKED.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <x86intrin.h>
#define ROWLEN 4096
#define MSIZE [ROWLEN][ROWLEN]
#define BLOCKSIZE 32


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

void dgemm_SIMD (int n, double* A, double* B, double* C){
    for ( int i = 0; i < n; i+=4 )
        for ( int j = 0; j < n; j++ ) {
            __m256d c0 = _mm256_load_pd(C+i+j*n); /* c0 = C[i][j] */
            for( int k = 0; k < n; k++ )
                c0 = _mm256_add_pd(c0, /* c0 += A[i][k]*B[k][j] */
                                   _mm256_mul_pd(_mm256_load_pd(A+i+k*n),_mm256_broadcast_sd(B+k+j*n)));
            _mm256_store_pd(C+i+j*n, c0); /* C[i][j] = c0 */
        }
}

void dgemmOld (int n, double* A, double* B, double* C){
    
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            double cij = C[j+i*n]; /* cij = C[i][j] */
            for( int k = 0; k < n; k++ )
                cij += A[k+i*n] * B[j+k*n]; /* cij += A[i][k]*B[k][j] */
            C[j+i*n] = cij; /* C[i][j] = cij */
        }
}

void dgemmPipelined (
                     int n, double* A, double* B, double* C)
{
    for ( int i = 0; i < n; i+=UNROLL*4 )
        for ( int j = 0; j < n; j++ ) {
            __m256d c[4];
            for ( int x = 0; x < UNROLL; x++ )
                c[x] = _mm256_load_pd(C+i+x*4+j*n);
            
            for( int k = 0; k < n; k++ )
            {
                __m256d b = _mm256_broadcast_sd(B+k+j*n);
                for (int x = 0; x < UNROLL; x++)
                    c[x] = _mm256_add_pd(c[x],
                                         _mm256_mul_pd(_mm256_load_pd(A+n*k+x*4+i), b));
            }
            
            for ( int x = 0; x < UNROLL; x++ )
                _mm256_store_pd(C+i+x*4+j*n, c[x]);
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


void do_block (int n, int si, int sj, int sk, double *A, double*B, double *C)
{
    for (int i = si; i < si+BLOCKSIZE; ++i)
        for (int j = sj; j < sj+BLOCKSIZE; ++j)
        {
            double cij = C[i+j*n];/* cij = C[i][j] */
            for( int k = sk; k < sk+BLOCKSIZE; k++ )
                cij += A[i+k*n] * B[k+j*n];/* cij+=A[i][k]*B[k][j] */
            C[i+j*n] = cij;/* C[i][j] = cij */
        }
}

void do_block_Parallel (int n, int si, int sj, int sk,
               double *A, double *B, double *C)
{
    for ( int i = si; i < si+BLOCKSIZE; i+=UNROLL*4 )
        for ( int j = sj; j < sj+BLOCKSIZE; j++ ) {
            __m256d c[4];
            for ( int x = 0; x < UNROLL; x++ )
                c[x] = _mm256_load_pd(C+i+x*4+j*n);
            /* c[x] = C[i][j] */
            for( int k = sk; k < sk+BLOCKSIZE; k++ )
            {
                __m256d b = _mm256_broadcast_sd(B+k+j*n);
                /* b = B[k][j] */
                for (int x = 0; x < UNROLL; x++)
                    c[x] = _mm256_add_pd(c[x], /* c[x]+=A[i][k]*b */
                    _mm256_mul_pd(_mm256_load_pd(A+n*k+x*4+i), b));
            }
            for ( int x = 0; x < UNROLL; x++ )
                _mm256_store_pd(C+i+x*4+j*n, c[x]);
            /* C[i][j] = c[x] */
        }
}

void dgemm_PAR (int n, double* A, double* B, double* C)
{
#pragma omp parallel for
    for ( int sj = 0; sj < n; sj += BLOCKSIZE )
        for ( int si = 0; si < n; si += BLOCKSIZE )
            for ( int sk = 0; sk < n; sk += BLOCKSIZE )
                do_block_Parallel(n, si, sj, sk, A, B, C);
}



void dgemm_CACHEBlocked (int n, double* A, double* B, double* C)
{
    for ( int sj = 0; sj < n; sj += BLOCKSIZE )
        for ( int si = 0; si < n; si += BLOCKSIZE )
            for ( int sk = 0; sk < n; sk += BLOCKSIZE )
                do_block(n, si, sj, sk, A, B, C);
}
