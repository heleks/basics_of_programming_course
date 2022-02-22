#include "matrix.h"
#include <stdlib.h>
#include <math.h>

//task 1

void swapMinMaxRows( matrix m ) {
    int min = getMinValuePos( m ).rowIndex;
    int max = getMaxValuePos( m ).rowIndex;

    swapRows( m , min , max );
}

//task 2

int getMax( int* a , int n ) {
    int maxValue = a[ 0 ];

    for ( int i = 0; i < n; ++i )
        if ( a[ i ] > maxValue )
            maxValue = a[ i ];

    return maxValue;
}

void sortRowsByMaxElement( matrix m ) {
    insertionSortRowsMatrixByRowCriteria( m , getMax );
}

//task 3

int getMin( int* a , int n ) {
    int minValue = a[ 0 ];

    for ( int i = 0; i < n; ++i )
        if ( a[ i ] < minValue )
            minValue = a[ i ];

    return minValue;
}

void sortColsByMinElement( matrix m ) {
    insertionSortColsMatrixByColCriteria( m , getMin );
}

//task 4

matrix mulMatrices( matrix m1 , matrix m2 ) {
    if ( m1.nCols != m2.nRows ) {
        printf( "[ error ] nCols and nRows not equal!" );
        exit( 1 );
    }

    matrix mul = getMemMatrix( m1.nRows , m2.nCols );

    for ( int i = 0; i < m1.nRows; ++i )
        for ( int j = 0; j < m2.nCols; ++j ) {
            mul.values[ i ][ j ] = 0;
            for ( int k = 0; k < m2.nRows; ++k )
                mul.values[ i ][ j ] += m1.values[ i ][ k ] * m2.values[ k ][ j ];
        }

    return mul;
}

void getSquareOfMatrixIfSymmetric( matrix* m ) {
    if ( isSymmetricMatrix( *m ) )
        *m = mulMatrices( *m , *m );
}

//task 5

bool isUnique( long long* a , int n ) {
    for ( int i = 0; i < n; i++ )
        for ( int j = i + 1; j < n; j++ )
            if ( a[ i ] == a[ j ] )
                return false;

    return true;
}

long long getSum( int* a , int n ) {
    long long sum = 0;

    for ( int i = 0; i < n; i++ )
        sum += a[ i ];

    return sum;
}

void transposeIfMatrixHasNotEqualSumOfRows( matrix m ) {
    long long* sumRows = ( long long* )malloc( sizeof( long long ) * m.nRows );

    for ( int i = 0; i < m.nRows; ++i )
        sumRows[ i ] = getSum( m.values[ i ] , m.nCols );

    if ( isUnique( sumRows , m.nRows ) )
        transposeSquareMatrix( &m );
    
    free( sumRows );
}

