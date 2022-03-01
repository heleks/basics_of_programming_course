#include "matrix.h"
#include "matrixD.h"
#include <stdlib.h>
#include <math.h>
#include <assert.h>

//task 1

void swapMinMaxRows( matrix m ) {
    int min = getMinValuePos( m ).rowIndex;
    int max = getMaxValuePos( m ).rowIndex;

    swapRows( m , min , max );
}

//task 2

int getMax( int* a , int n ) {
    int maxValue = a[ 0 ];

    for ( int i = 1; i < n; ++i )
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

    for ( int i = 1; i < n; ++i )
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
    if ( isSymmetricMatrix( *m ) ) {
        matrix r = mulMatrices( *m , *m );
        freeMemMatrix( *m );
        *m = r;
    }
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

void transposeIfMatrixHasNotEqualSumOfRows( matrix* m ) {
    long long* sumRows = ( long long* )malloc( sizeof( long long ) * m->nRows );

    for ( int i = 0; i < m->nRows; ++i )
        sumRows[ i ] = getSum( m->values[ i ] , m->nCols );

    if ( isUnique( sumRows , m->nRows ) )
        transposeSquareMatrix( m );
    
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

// task 11

int getNSpecialElement( matrix m ) {
    int count = 0;

    for ( int i = 0; i < m.nCols; ++i ) {
        int* colArray = ( int* )malloc( sizeof( int ) * m.nRows );

        for ( int j = 0; j < m.nRows; j++ ) 
            colArray[ j ] = m.values[ j ][ i ];

        if ( getMax( colArray , m.nRows ) * 2 - getSum( colArray , m.nRows ) > 0 )
            ++count;

        free( colArray );
    }

    return count;
}

// task 12

position getLeftMin( matrix m ) {
    return getMinValuePos( m );
}

void swapPenultimateRow( matrix m ) {
    if ( !isSquareMatrix( m ) )
        return;

    int colIndex = getLeftMin( m ).colIndex;

    for ( int i = m.nCols - 1; i >= 0; --i )
        m.values[ m.nRows - 2 ][ i ] = m.values[ i ][ colIndex ];
}

//task 13

bool isNonDescendingSorted( int* a , int size ) {
    for ( int i = 1; i < size; ++i )
        if ( a[ i - 1 ] > a[ i ] )
            return false;

    return true;
}

bool hasAllNonDescendingRows( matrix m ) {
    int count = 0;

    for ( int i = 0; i < m.nRows; ++i )
        count += isNonDescendingSorted( m.values[ i ] , m.nCols );
   
    return count == m.nRows;
}

int countNonDescendingRowsMatrices( matrix* ms , int nMatrix ) {
    int count = 0;

    for ( int i = 0; i < nMatrix; ++i )
        count += hasAllNonDescendingRows( ms[ i ] );

    return count;
}

//task 14

int countZeroValues( int* a , int size ) {
    int count = 0;

    for ( int i = 0; i < size; ++i )
        count += a[ i ] == 0;
   
    return count;
}

int countZeroRows( matrix m ) {
    int count = 0;

    for ( int i = 0; i < m.nRows; ++i )
        count += countZeroValues( m.values[ i ] , m.nCols ) == m.nCols;
    
    return count;
}

void printMatrixWithMaxZeroRows( matrix* ms , int nMatrix ) {
    int maxZeroRows = countZeroRows( ms[ 0 ] );

    for ( int i = 1; i < nMatrix; ++i ) {
        int counterZeroRows = countZeroRows( ms[ i ] );

        if ( maxZeroRows < counterZeroRows )
            maxZeroRows = counterZeroRows;
    }

    for ( int i = 0; i < nMatrix; ++i )
        if ( countZeroRows( ms[ i ] ) == maxZeroRows )
            outputMatrix( ms[ i ] );
}

//task 15

double getMatrixAbsValue( matrixD m ) {
    double matrixAbsValue = 0.f;

    for ( int i = 0; i < m.nRows; ++i )
        for ( int j = 0; j < m.nCols; ++j )
            matrixAbsValue += fabs( m.values[ i ][ j ] );

    return matrixAbsValue;
}

matrixD getLowerNormMatrix( matrixD* ms , double* matricesLowerNorm , int nMatrix , float** skip ) {
    bool flag = skip == ms[ 0 ].values;
    double minValue = flag ? matricesLowerNorm[ 1 ] : matricesLowerNorm[ 0 ];
    matrixD minMatrix = flag ? ms[ 1 ] : ms[ 0 ];

    for ( int i = 1 + flag; i < nMatrix; ++i )
        if ( matricesLowerNorm[ i ] < minValue && skip != ms[ i ].values ) {
            minValue = matricesLowerNorm[ i ];
            minMatrix = ms[ i ];
        }

    return minMatrix;
}

void printLowerNormMatrices( matrixD* ms , int nMatrix ) {
    double* matricesLowerNorm = ( double* )malloc( sizeof( double ) * nMatrix );

    for ( int i = 0; i < nMatrix; ++i )
        matricesLowerNorm[ i ] = getMatrixAbsValue( ms[ i ] );

    matrixD lowerNormMatrices[ 2 ] = { NULL , NULL };

    lowerNormMatrices[ 0 ] = getLowerNormMatrix( ms , matricesLowerNorm , nMatrix , NULL );
    lowerNormMatrices[ 1 ] = getLowerNormMatrix( ms , matricesLowerNorm , nMatrix , lowerNormMatrices[ 0 ].values );

    free( matricesLowerNorm );

    outputMatricesD( lowerNormMatrices , 2 );
}

void test_swapMinMaxRows( ) {
    int nRows = 2;
    int nCols = 2;
    matrix m = createMatrixFromArray( ( int[ ] ) { 1 , 2 , 3 , 4 } , nRows , nCols );
    matrix r = createMatrixFromArray( ( int[ ] ) { 3 , 4 , 1 , 2} , nRows , nCols );

    swapMinMaxRows( m );

    assert( areTwoMatricesEqual( m , r ) == true );

    freeMemMatrix( m );
}

void test_sortRowsByMaxElement( ) {
    int nRows = 3;
    int nCols = 3;
    matrix m = createMatrixFromArray( ( int[ ] ) { 7 , 1 , 2 , 1 , 8 , 1 , 3 , 2 , 3 } , nRows , nCols );
    matrix r = createMatrixFromArray( ( int[ ] ) { 3 , 2 , 3 , 7 , 1 , 2 , 1 , 8 , 1 } , nRows , nCols );

    sortRowsByMaxElement( m );

    assert( areTwoMatricesEqual( m , r ) == true );

    freeMemMatrix( m );
    freeMemMatrix( r );
}

void test_sortColsByMinElement( ) {
    int nRows = 3;
    int nCols = 6;
    matrix m = createMatrixFromArray( ( int[ ] ) { 3 , 5 , 2 , 4 , 3 , 3 , 2 , 5 , 1 , 8 , 2 , 7 , 6 , 1 , 4 , 4 , 8 , 3 } , nRows , nCols );
    matrix r = createMatrixFromArray( ( int[ ] ) { 5 , 2 , 3 , 3 , 3 , 4 , 5 , 1 , 2 , 2 , 7 , 8 , 1 , 4 , 6 , 8 , 3 , 4 } , nRows , nCols );

    sortColsByMinElement( m );

    assert( areTwoMatricesEqual( m , r ) == true );

    freeMemMatrix( m );
    freeMemMatrix( r );
}

void test_getSquareOfMatrixIfSymmetric( ) {
    int nRows = 2;
    int nCols = 2;
    matrix m = createMatrixFromArray( ( int[ ] ) { 1 , 5 , 5 , 7  } , nRows , nCols );
    matrix r = createMatrixFromArray( ( int[ ] ) { 26 , 40 , 40 , 74 } , nRows , nCols );

    getSquareOfMatrixIfSymmetric( &m );

    assert( areTwoMatricesEqual( m , r ) == true );

    freeMemMatrix( m );
    freeMemMatrix( r );
}

void test_transposeIfMatrixHasNotEqualSumOfRows( ) {
    int nRows = 3;
    int nCols = 3;
    matrix m = createMatrixFromArray( ( int[ ] ) { 1 , 2 , 3 , 1 , 2 , 0 , 2 , 0 , 0 } , nRows , nCols );
    matrix r = createMatrixFromArray( ( int[ ] ) { 1 , 1 , 2 , 2 , 2 , 0 , 3 , 0 , 0 } , nRows , nCols );

    transposeIfMatrixHasNotEqualSumOfRows( &m );

    assert( areTwoMatricesEqual( m , r ) == true );

    freeMemMatrix( m );
    freeMemMatrix( r );
}

void test_isMutuallyInverseMatrices( ) {
    int nRows = 2;
    int nCols = 2;
    matrix m1 = createMatrixFromArray( ( int[ ] ) { 3 , 4 , 1 , 1 } , nRows , nCols );
    matrix m2 = createMatrixFromArray( ( int[ ] ) { -1 , 4 , 1 , -3 } , nRows , nCols );

    assert( isMutuallyInverseMatrices( m1 , m2 ) == true );

    freeMemMatrix( m1 );
    freeMemMatrix( m2 );
}

void test_findSumOfMaxesOfPseudoDiagonal( ) {
    int nRows = 3;
    int nCols = 4;
    matrix m = createMatrixFromArray( ( int[ ] ) { 3 , 2 , 5 , 4 , 1 , 3 , 6 , 3 , 3 , 2 , 1 , 2 } , nRows , nCols );
    
    assert( findSumOfMaxesOfPseudoDiagonal( m ) == 20 );

    freeMemMatrix( m );
}

void test_getMinInArea( ) {
    int nRows = 2;
    int nCols = 2;
    matrix m = createMatrixFromArray( ( int[ ] ) { 1 , 2 , 3 , 4 } , nRows , nCols );

    assert( getMinInArea( m ) == 1 );

    freeMemMatrix( m );
}

void test_sortByDistance( ) {
    int nRows = 2;
    int nCols = 2;
    matrix m1 = createMatrixFromArray( ( int[ ] ) { 3 , 4 , 1 , 1 } , nRows , nCols );
    matrix m2 = createMatrixFromArray( ( int[ ] ) { 1 , 1 , 3 , 4 } , nRows , nCols );

    sortByDistance( m1 );

    assert( areTwoMatricesEqual( m1 , m2 ) == true );

    freeMemMatrix( m1 );
    freeMemMatrix( m2 );
}

void test_countEqClassesByRowsSum( ) {
    int nRows = 6;
    int nCols = 2;
    matrix m = createMatrixFromArray( ( int[ ] ) { 7 , 1 , 2 , 7 , 5 , 4 , 4 , 3 , 1 , 6 , 8 , 0 } , nRows , nCols );
    
    assert( countEqClassesByRowsSum( m ) == 4 );

    freeMemMatrix( m );
}

void test_getNSpecialElement( ) {
    int nRows = 3;
    int nCols = 4;
    matrix m = createMatrixFromArray( ( int[ ] ) { 3 , 5 , 5 , 4 , 2 , 3 , 6 , 7 , 12 , 2 , 1 , 2 } , nRows , nCols );

    assert( getNSpecialElement( m ) == 2 );

    freeMemMatrix( m );
}

void test_swapPenultimateRow( ) {
    int nRows = 3;
    int nCols = 3;
    matrix m1 = createMatrixFromArray( ( int[ ] ) { 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 1 } , nRows , nCols );
    matrix m2 = createMatrixFromArray( ( int[ ] ) { 1 , 2 , 3 , 1 , 4 , 7 , 7 , 8 , 1 } , nRows , nCols );

    swapPenultimateRow( m1 );

    assert( areTwoMatricesEqual( m1 , m2 ) == true );

    freeMemMatrix( m1 );
    freeMemMatrix( m2 );
}

void test_countNonDescendingRowsMatrices( ) {
    int nRows = 2;
    int nCols = 2;
    int nMatrix = 4;
    matrix* ms = createArrayOfMatrixFromArray( ( int[ ] ) { 
        7 , 1 , 
        1 , 1 , 

        1 , 6 ,      
        2 , 2 ,

        5 , 4 ,
        2 , 3 ,

        1 , 3 ,
        7 , 9
    } , nMatrix , nRows , nCols );

    assert( countNonDescendingRowsMatrices( ms , nMatrix ) == 2 );

    freeMemMatrices( ms , nMatrix );
}

void test_countZeroRows( ) {
    int nRows = 3;
    int nCols = 2;
    int nMatrix = 5;
    matrix* ms = createArrayOfMatrixFromArray( ( int[ ] ) {
        0 , 1 ,
        1 , 0 ,
        0 , 0 ,

        1 , 1 ,
        2 , 1 ,
        1 , 1 ,

        0 , 0 ,
        0 , 0 ,
        4 , 7 ,

        0 , 0 ,
        0 , 1 ,
        0 , 0 ,

        0 , 1 ,
        0 , 2 ,
        0 , 3 ,
    } , nMatrix , nRows , nCols );

    int results[ ] = { 1, 0, 2, 2, 0 };

    for ( int i = 0; i < 5; ++i )
        assert( countZeroRows( ms[ i ] ) == results[ i ] );

    freeMemMatrices( ms , 5 );
}

void test_getLowerNormMatrix( ) {
    int nRows = 2;
    int nCols = 2;
    int nMatrix = 3;
    matrixD* ms = createArrayOfMatrixFromArrayD( ( double[ ] ) {
        4 , 5 ,
        6 , 7 ,

        1 , 2 ,
        3 , 4 , 

        7 , 8 ,
        9 , 10
    } , nMatrix , nRows , nCols );

    double* matricesLowerNorm = ( double* )malloc( sizeof( double ) * nMatrix );

    for ( int i = 0; i < nMatrix; ++i )
        matricesLowerNorm[ i ] = getMatrixAbsValue( ms[ i ] );

    matrixD lowerNormMatrices[ 2 ] = { NULL , NULL };

    lowerNormMatrices[ 0 ] = getLowerNormMatrix( ms , matricesLowerNorm , nMatrix , NULL );
    lowerNormMatrices[ 1 ] = getLowerNormMatrix( ms , matricesLowerNorm , nMatrix , lowerNormMatrices[ 0 ].values );

    free( matricesLowerNorm );

    assert( ms[ 1 ].values == lowerNormMatrices[ 0 ].values );

    freeMemMatricesD( ms , 2 );
}

void tests_tasks( ) {
    test_swapMinMaxRows( );
    test_sortRowsByMaxElement( );
    test_sortColsByMinElement( );
    test_getSquareOfMatrixIfSymmetric( );
    test_transposeIfMatrixHasNotEqualSumOfRows( );
    test_isMutuallyInverseMatrices( );
    test_findSumOfMaxesOfPseudoDiagonal( );
    test_getMinInArea( );
    test_sortByDistance( );
    test_countEqClassesByRowsSum( );
    test_getNSpecialElement( );
    test_swapPenultimateRow( );
    test_countNonDescendingRowsMatrices( );
    test_countZeroRows( );
    test_getLowerNormMatrix( );
}

