#ifndef __ETHREAD_H
#define __ETHREAD_H

#include <stdlib.h>
#include <stdio.h>

typedef struct matrix{
    int area; //n x n size
    int nSize; //row size
    int* m; //matrix a
    int* e;  //u vector matrix
    int product; 
    // EigenVector* result; 
}Matrix;


typedef struct data{
    Matrix* data; 
}Data;

void setupRows(Data* row, int area, int nSz);
void* calculateEigenVector(void* arg);
void freeMatrices(Data* args, int nSz);
void printResults(Data* args, int nSz);

#endif
