#ifndef matrix_h
#define matrix_h

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>


typedef struct matrix {
	int** values;
	int nRows;
	int nCols;
} matrix;

typedef struct position {
	int rowIndex;
	int colIndex;
} position;

matrix getMemMatrix( int nRows , int nCols );

matrix* getMemArrayOfMatrices( int nMatrices , int nRows , int nCols );

void freeMemMatrix( matrix m );

void freeMemMatrices( matrix* ms , int nMatrices );

void inputMatrix( matrix m );

void inputMatrices( matrix* ms , int nMatrices );

void outputMatrix( matrix m );

void outputMatrices( matrix* ms , int nMatrices );

void swapRows( matrix m , int i1 , int i2 );

void swapColumns( matrix m , int j1 , int j2 );

void insertionSortRowsMatrixByRowCriteria( matrix m , int ( *criteria )( int* , int ) );

void insertionSortColsMatrixByColCriteria( matrix m , int ( *criteria )( int* , int ) );

bool isSquareMatrix( matrix m );

bool areTwoMatricesEqual( matrix m1 , matrix m2 );

bool isEMatrix( matrix m );

bool isSymmetricMatrix( matrix m );

void transposeSquareMatrix( matrix* m );

position getMinValuePos( matrix m );

position getMaxValuePos( matrix m );

matrix createMatrixFromArray( const int* a , int nRows , int nCols );

matrix* createArrayOfMatrixFromArray( const int* a , int nMatrix , int nRows , int nCols );

#endif