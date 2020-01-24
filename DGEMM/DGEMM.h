//
//  DGEMM.h
//  DGEMM
//
//  Created by Steven Moody on 1/23/20.
//  Copyright © 2020 Steven Moody. All rights reserved.
//

#ifndef DGEMM_h
#define DGEMM_h

#define ROWLEN 1024
#define MSIZE [ROWLEN][ROWLEN]

    void ge(int n, double* A, double* B, double* C);

    void mm(double a[ROWLEN][ROWLEN], double b[ROWLEN][ROWLEN], double c[ROWLEN][ROWLEN]);
    
    void dgemm (int n, double* A, double* B, double* C);

    void output(int n, double* A, double* B, double* C);


#endif /* DGEMM_h */

