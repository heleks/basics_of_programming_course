#include <assert.h>
#include "matrix.h"

void test_getMemMatrix( ) {
    int nRows = 2;
    int nCols = 2;
    matrix m = getMemMatrix( nRows , nCols );

    assert( m.values != NULL );
    assert( m.nRows == nRows );
    assert( m.nCols == nCols );

    for ( int i = 0; i < nRows; ++i )
        for ( int j = 0; j < nCols; ++j )
            assert( m.values[ i ][ j ] != NULL );

    freeMemMatrix( m );
}

void test_getMemArrayOfMatrices( ) {
    int nMatrices = 2;
    int nRows = 2;
    int nCols = 2;
    matrix* m = getMemArrayOfMatrices( nMatrices , nRows , nCols );

    for ( int c = 0; c < nRows; ++c )
        for ( int j = 0; j < nRows; ++j )
            for ( int i = 0; i < nCols; ++i )
                assert( m[ c ].values[ i ][ j ] != NULL );

    freeMemMatrices( m , nMatrices );
}

void test_swapRows( ) {
    int nRows = 2;
    int nCols = 2;
    matrix m = createMatrixFromArray( ( int[ ] ) { 1 , 2 , 3 , 4 } , nRows , nCols );

    swapRows( m , 0 , 1 );

    assert( m.values[ 0 ][ 0 ] == 3 );
    assert( m.values[ 0 ][ 1 ] == 4 );
    assert( m.values[ 1 ][ 0 ] == 1 );
    assert( m.values[ 1 ][ 1 ] == 2 );

    freeMemMatrix( m );
}

void test_swapColumns( ) {
    int nRows = 2;
    int nCols = 2;
    matrix m = createMatrixFromArray( ( int[ ] ) { 1 , 2 , 3 , 4 } , nRows , nCols );

    swapColumns( m , 0 , 1 );

    assert( m.values[ 0 ][ 0 ] == 2 );
    assert( m.values[ 0 ][ 1 ] == 1 );
    assert( m.values[ 1 ][ 0 ] == 4 );
    assert( m.values[ 1 ][ 1 ] == 3 );

    freeMemMatrix( m );
}

int arraySum( int* a , int n ) {
    int sum = 0;
    for ( int i = 0; i < n; ++i )
        sum += a[ i ];

    return sum;
}

void test_insertionSortRowsMatrixByRowCriteria( ) {
    matrix m1 = createMatrixFromArray( ( int[ ] ) { 1 , 2 , 3 ,  4 , 5 , 6 , 7 , 8 , 9 } , 3 , 3 );
    matrix m2 = createMatrixFromArray( ( int[ ] ) { 7 , 8 , 9 , 4 , 5 , 6 , 1 , 2 , 3 } , 3 , 3 );

    insertionSortRowsMatrixByRowCriteria( m2 , arraySum );

    assert( areTwoMatricesEqual( m1 , m2 ) );

    freeMemMatrix( m1 );
    freeMemMatrix( m2 );
}

void test_insertionSortColsMatrixByColCriteria( ) {
    matrix m1 = createMatrixFromArray( ( int[ ] ) { 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 } , 3 , 3 );
    matrix m2 = createMatrixFromArray( ( int[ ] ) { 3 , 2 , 1 , 6 , 5 , 4 , 9 , 8 , 7 } , 3 , 3 );

    insertionSortColsMatrixByColCriteria( m2 , arraySum );

    assert( areTwoMatricesEqual( m1 , m2 ) );

    freeMemMatrix( m1 );
    freeMemMatrix( m2 );
}

void test_isSquareMatrix1( ) {
    int nRows = 2;
    int nCols = 2;
    matrix m = getMemMatrix( nRows , nCols );

    assert( isSquareMatrix( m ) == true );

    freeMemMatrix( m );
}

void test_isSquareMatrix2( ) {
    int nRows = 2;
    int nCols = 3;
    matrix m = getMemMatrix( nRows , nCols );

    assert( isSquareMatrix( m ) == false );

    freeMemMatrix( m );
}

void test_areTwoMatricesEqual1( ) {
    int nRows = 2;
    int nCols = 2;

    matrix m1 = createMatrixFromArray( ( int[ ] ) { 1 , 2 , 3 ,4 } , nRows , nCols );
    matrix m2 = createMatrixFromArray( ( int[ ] ) { 1 , 2 , 3 , 4 } , nRows , nCols );

    assert( areTwoMatricesEqual( m1 , m2 ) == true );

    freeMemMatrix( m1 );
    freeMemMatrix( m2 );
}

void test_areTwoMatricesEqual2( ) {
    int nRows = 2;
    int nCols = 2;
    matrix m1 = createMatrixFromArray( ( int[ ] ) { 1 , 2 , 3 , 4 } , nRows , nCols );

    matrix m2 = createMatrixFromArray( ( int[ ] ) { 1 , 2 , 3 , 4 , 5 , 6 } , nRows + 1 , nCols );

    assert( areTwoMatricesEqual( m1 , m2 ) == false );

    freeMemMatrix( m1 );
    freeMemMatrix( m2 );
}

void test_isEMatrix1( ) {
    int nRows = 2;
    int nCols = 2;
    matrix m = createMatrixFromArray( ( int[ ] ) { 1 , 0 , 0 , 1 } , nRows , nCols );

    assert( isEMatrix( m ) == true );

    freeMemMatrix( m );
}

void test_isEMatrix2( ) {
    int nRows = 2;
    int nCols = 3;
    matrix m = createMatrixFromArray( ( int[ ] ) { 1 , 0 , 0 , 1 , 0 , 0 } , nRows , nCols );

    assert( isEMatrix( m ) == false );

    freeMemMatrix( m );
}

void test_isSymmetricMatrix1( ) {
    int nRows = 2;
    int nCols = 2;
    matrix m = createMatrixFromArray( ( int[ ] ) { 1 , 5 , 5 , 7 } , nRows , nCols );

    assert( isSymmetricMatrix( m ) == true );

    freeMemMatrix( m );
}

void test_isSymmetricMatrix2( ) {
    int nRows = 2;
    int nCols = 3;
    matrix m = createMatrixFromArray( ( int[ ] ) { 1 , 5 , 5 , 7 , 0 , 0 } , nRows , nCols );

    assert( isSymmetricMatrix( m ) == false );

    freeMemMatrix( m );
}

void test_transposeSquareMatrix1( ) {
    int nRows = 2;
    int nCols = 2;
    matrix m = createMatrixFromArray( ( int[ ] ) { 1 , 2 , 3 , 4 } , nRows , nCols );

    transposeSquareMatrix( &m );

    assert( m.values[ 0 ][ 0 ] == 1 );
    assert( m.values[ 0 ][ 1 ] == 3 );
    assert( m.values[ 1 ][ 0 ] == 2 );
    assert( m.values[ 1 ][ 1 ] == 4 );

    freeMemMatrix( m );
}

void test_transposeSquareMatrix2( ) {
    int nRows = 3;
    int nCols = 2;
    matrix m = createMatrixFromArray( ( int[ ] ) { 1 , 2 , 3 , 4 , 5 , 6 } , nRows , nCols );

    transposeSquareMatrix( &m );

    assert( m.nCols != nRows );

    freeMemMatrix( m );
}

void test_getMinValuePos( ) {
    int nRows = 2;
    int nCols = 2;
    matrix m = createMatrixFromArray( ( int[ ] ) { 1 , 2 , 0 , 4 } , nRows , nCols );

    position pos = getMinValuePos( m );

    assert( pos.rowIndex == 1 && pos.colIndex == 0 );

    freeMemMatrix( m );
}

void test_getMaxValuePos( ) {
    int nRows = 2;
    int nCols = 2;
    matrix m = createMatrixFromArray( ( int[ ] ) { 1 , 2 , 9 , 4 } , nRows , nCols );

    position pos = getMaxValuePos( m );

    assert( pos.rowIndex == 1 && pos.colIndex == 0 );

    freeMemMatrix( m );
}

void tests( ) {
    test_getMemMatrix( );
    test_getMemArrayOfMatrices( );
    test_swapRows( );
    test_swapColumns( );
    test_insertionSortRowsMatrixByRowCriteria( );
    test_insertionSortColsMatrixByColCriteria( );
    test_isSquareMatrix1( );
    test_isSquareMatrix2( );
    test_areTwoMatricesEqual1( );
    test_areTwoMatricesEqual2( );
    test_isEMatrix1( );
    test_isEMatrix2( );
    test_isSymmetricMatrix1( );
    test_isSymmetricMatrix2( );
    test_transposeSquareMatrix1( );
    test_transposeSquareMatrix2( );
    test_getMinValuePos( );
    test_getMaxValuePos( );
}
