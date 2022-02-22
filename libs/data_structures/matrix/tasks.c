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
