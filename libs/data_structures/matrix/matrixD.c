//#include "matrixD.h"
//
//matrixD getMemMatrixD( int nRows , int nCols ) {
//    double** values = ( double** )malloc( sizeof( double* ) * nRows );
//
//    for ( int i = 0; i < nRows; ++i )
//        values[ i ] = ( double* )malloc( sizeof( double ) * nCols );
//
//    return ( matrixD ) { values , nRows , nCols };
//}
//
//
//matrixD* getMemArrayOfMatricesD( int nMatrices , int nRows , int nCols ) {
//    matrixD* ms = ( matrixD* )malloc( sizeof( matrixD ) * nMatrices );
//
//    for ( int i = 0; i < nMatrices; ++i )
//        ms[ i ] = getMemMatrixD( nRows , nCols );
//
//    return ms;
//}
//
//void freeMemMatrixD( matrixD m ) {
//    for ( int i = 0; i < m.nRows; ++i )
//        free( m.values[ i ] );
//
//    free( m.values );
//}
//
//void freeMemMatricesD( matrixD* ms , int nMatrices ) {
//    for ( int i = 0; i < nMatrices; ++i )
//        freeMemMatrixD( ms[ i ] );
//}
//
//void inputMatrixD( matrixD m ) {
//    for ( int i = 0; i < m.nRows; ++i )
//        for ( int j = 0; j < m.nCols; ++j )
//            scanf( "%lf" , &m.values[ i ][ j ] );
//}
//
//void inputMatricesD( matrixD* ms , int nMatrices ) {
//    for ( int i = 0; i < nMatrices; ++i )
//        inputMatrixD( ms[ i ] );
//}
//
//void outputMatrixD( matrixD m ) {
//    for ( int i = 0; i < m.nRows; ++i ) {
//        for ( int j = 0; j < m.nCols; ++j )
//            printf( "%lf " , m.values[ i ][ j ] );
//
//        printf( "\n" );
//    }
//
//    printf( "\n" );
//}
//
//void outputMatricesD( matrixD* ms , int nMatrices ) {
//    for ( int i = 0; i < nMatrices; ++i )
//        outputMatrixD( ms[ i ] );
//}
//
//matrixD* createArrayOfMatrixFromArrayD( const double* a , int nMatrix , int nRows , int nCols ) {
//    matrixD* m = getMemArrayOfMatricesD( nMatrix , nRows , nCols );
//
//    int k = 0;
//    for ( int l = 0; l < nMatrix; ++l )
//        for ( int i = 0; i < nRows; i++ )
//            for ( int j = 0; j < nCols; j++ )
//                m[ l ].values[ i ][ j ] = a[ k++ ];
//
//    return m;
//}
