#include "matrix.h"

void swapMinMaxRows( matrix m ) {
    int min = getMinValuePos( m ).rowIndex;
    int max = getMaxValuePos( m ).rowIndex;

    swapRows( m , min , max );
}

//https://prnt.sc/26wigmu