#ifndef matrixD_h
#define matrixD_h

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct matrixD {
    double** values;
    int nRows;
    int nCols;
} matrixD;

matrixD getMemMatrixD( int nRows , int nCols );

matrixD* getMemArrayOfMatricesD( int nMatrices , int nRows , int nCols );

void freeMemMatrixD( matrixD m );

void freeMemMatricesD( matrixD* ms , int nMatrices );

void inputMatrixD( matrixD m );

void inputMatricesD( matrixD* ms , int nMatrices );

void outputMatrixD( matrixD m );

void outputMatricesD( matrixD* ms , int nMatrices );

#endif