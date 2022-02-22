#include "matrix.h"
#include "matrixD.h"
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

//task 6

bool isMutuallyInverseMatrices( matrix m1 , matrix m2 ) {
    if ( !isSquareMatrix( m1 ) || !isSquareMatrix( m2 ) )
        return false;

    matrix mul = mulMatrices( m1 , m2 );
    bool result = isEMatrix( mul );
    freeMemMatrix( mul );

    return result;
}

//task 7

int max2( int a , int b ) {
    return a > b ? a : b;
}

long long findSumOfMaxesOfPseudoDiagonal( matrix m ) {
    long long sum = 0;

    for ( int i = 1; i < m.nCols; ++i ) {
        int maxValue = m.values[ 0 ][ i ];

        for ( int j = i + 1; j < m.nCols; ++j )
            maxValue = max2( maxValue , m.values[ j - 1 ][ j ] );

        sum += maxValue;
    }

    for ( int i = 1; i < m.nRows; ++i ) {
        int maxValue1 = m.values[ i ][ 0 ];

        for ( int j = i + 1; j < m.nRows; ++j )
            maxValue1 = max2( maxValue1 , m.values[ j ][ j - 1 ] );

        sum += maxValue1;
    }

    return sum;
}

//task 8

int min2( int a , int b ) {
    return a < b ? a : b;
}

int getMinInArea( matrix m ) {
    position maxValue = getMaxValuePos( m );
    int minInArea = m.values[ maxValue.rowIndex ][ maxValue.colIndex ];
    int firstColIndex = maxValue.colIndex;
    int secondColIndex = maxValue.colIndex;

    for ( int i = maxValue.rowIndex - 1; i >= 0; --i ) {
        if ( secondColIndex + 1 > m.nCols - 1 )
            secondColIndex = m.nCols - 1;
        else
            ++secondColIndex;

        if ( firstColIndex - 1 < 0 )
            firstColIndex = 0;
        else
            --firstColIndex;

        minInArea = min2( minInArea , getMin( m.values[ i ] + firstColIndex , secondColIndex - firstColIndex + 1 ) );
    }

    return minInArea;
}

//task 9

float getDistance( int* a , int size ) {
    double sum = 0.0;

    for ( int i = 0; i < size; ++i )
        sum += pow( ( double )a[ i ] , 2.0 );
    
    return ( float )sqrt( sum );
}

void insertionSortRowsMatrixByRowCriteriaF( matrix m , float ( *criteria )( int * , int ) ) {
    for ( int i = 1; i < m.nRows; ++i )
        for ( int j = i; j > 0; --j ) 
            if ( criteria( m.values[ j - 1 ] , m.nCols ) > criteria( m.values[ j ] , m.nCols ) ) 
                swapRows( m , j - 1 , j );
}

void sortByDistance( matrix m ) {
    insertionSortRowsMatrixByRowCriteriaF( m , getDistance );
}

// task 10

int long_long_cmp( const void* x , const void* y ) {
    long long a = *( long long* )x;
    long long b = *( long long* )y;

    if ( a < b )
        return -1;
    else if ( a > b )
        return 1;
    else
        return 0;
}

int countNUnique( const long long* a , int n ) {
    if ( n == 0 )
        return 0;
    else {
        long long element = a[ 0 ];
        int nUnique = 1;

        for ( int i = 1; i < n; i++ )
            if ( a[ i ] != element ) {
                element = a[ i ];
                ++nUnique;
            }

        return nUnique;
    }
}

int countEqClassesByRowsSum( matrix m ) {
    long long* sumRows = ( long long* )malloc( sizeof( long long ) * m.nRows );

    for ( int i = 0; i < m.nRows; i++ )
        sumRows[ i ] = getSum( m.values[ i ] , m.nCols );

    int nUnique = countNUnique( sumRows , m.nRows );

    free( sumRows );

    return nUnique;
}
