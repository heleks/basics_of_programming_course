#include "matrix.h"

matrix getMemMatrix( int nRows , int nCols ) {
	int** values = ( int** )malloc( sizeof( int* ) * nRows );

	for ( int i = 0; i < nRows; ++i )
		values[ i ] = ( int* )malloc( sizeof( int ) * nCols );

	return ( matrix ) { values , nRows , nCols };
}

matrix* getMemArrayOfMatrices( int nMatrices , int nRows , int nCols ) {
	matrix* ms = ( matrix* )malloc( sizeof( matrix ) * nMatrices );

	for ( int i = 0; i < nMatrices; ++i )
		ms[ i ] = getMemMatrix( nRows , nCols );

	return ms;
}

void freeMemMatrix( matrix m ) {
	for ( int i = 0; i < m.nRows; ++i )
		free( m.values[ i ] );

	free( m.values );
}

void freeMemMatrices( matrix* ms , int nMatrices ) {
	for ( int i = 0; i < nMatrices; ++i )
		freeMemMatrix( ms[ i ] );
}

void inputMatrix( matrix m ) {
	for ( int i = 0; i < m.nRows; ++i )
		for ( int j = 0; j < m.nCols; ++j )
			scanf( "%d" , &m.values[ i ][ j ] );
}

void inputMatrices( matrix* ms , int nMatrices ) {
	for ( int i = 0; i < nMatrices; ++i )
		inputMatrix( ms[ i ] );
}

void outputMatrix( matrix m ) {
	for ( int i = 0; i < m.nRows; ++i ) {
		for ( int j = 0; j < m.nCols; ++j )
			printf( "%d " , m.values[ i ][ j ] );

		printf( "\n" );
	}
}

void outputMatrices( matrix* ms , int nMatrices ) {
	for ( int i = 0; i < nMatrices; ++i )
		outputMatrix( ms[ i ] );
}

void swap( int* a , int* b ) {
	int* temp = *a;

	*a = *b;
	*b = temp;
}

void swapRows( matrix m , int i1 , int i2 ) {
	swap( &m.values[ i1 ] , &m.values[ i2 ] );
}

void swapColumns( matrix m , int j1 , int j2 ) {
	for ( int i = 0; i < m.nRows; ++i )
		swap( &m.values[ i ][ j1 ] , &m.values[ i ][ j2 ] );
}

void insertionSortRowsMatrixByRowCriteria( matrix m , int ( *criteria )( int* , int ) ) {
	int* criteriaArray = ( int* )malloc( sizeof( int ) * m.nRows );

	for ( int i = 0; i < m.nRows; ++i )
		criteriaArray[ i ] = criteria( m.values[ i ] , m.nCols );

	for ( int i = 0; i < m.nRows; ++i )
		for ( int j = i; j > 0 && criteriaArray[ j - 1 ] > criteriaArray[ j ]; --j ) {
			swap( &criteriaArray[ j - 1 ] , &criteriaArray[ j ] , sizeof( int ) );
			swapRows( m , j , j - 1 );
		}

	free( criteriaArray );
}

void insertionSortColsMatrixByColCriteria( matrix m , int ( *criteria )( int* , int ) ) {
	int* criteriaArray = ( int* )malloc( sizeof( int ) * m.nCols );
	int* addArray = ( int* )malloc( sizeof( int ) * m.nRows );

	for ( int i = 0; i < m.nCols; ++i ) {
		for ( int j = 0; j < m.nRows; ++j )
			addArray[ j ] = m.values[ j ][ i ];
		criteriaArray[ i ] = criteria( addArray , m.nRows );
	}

	for ( int i = 0; i < m.nCols; ++i ) {
		for ( int j = i; j > 0 && criteriaArray[ j - 1 ] > criteriaArray[ j ]; --j ) {
			swap( &criteriaArray[ j - 1 ] , &criteriaArray[ j ] , sizeof( int ) );
			swapColumns( m , j , j - 1 );
		}
	}

	free( criteriaArray );
	free( addArray );
}

bool isSquareMatrix( matrix m ) {
	return m.nRows == m.nCols;
}

bool areTwoMatricesEqual( matrix m1 , matrix m2 ) {
	if ( m1.nRows * m1.nCols != m2.nRows * m2.nCols )
		return false;

	for ( int i = 0; i < m1.nRows; ++i )
		for ( int j = 0; j < m1.nCols; ++j )
			if ( m1.values[ i ][ j ] != m2.values[ i ][ j ] )
				return false;

	return true;
}

bool isEMatrix( matrix m ) {
	if ( !isSquareMatrix( m ) )
		return false;

	for ( int i = 0; i < m.nRows; ++i )
		for ( int j = 0; j < m.nCols; ++j )
			if ( i == j ) {
				if ( m.values[ i ][ i ] != 1 )
					return false;
			}
			else
				if ( m.values[ i ][ j ] != 0 )
					return false;

	return true;
}

bool isSymmetricMatrix( matrix m ) {
	if ( !isSquareMatrix( m ) )
		return false;

	for ( int i = 0; i < m.nRows; ++i )
		for ( int j = i + 1; j < m.nCols; ++j )
			if ( m.values[ i ][ j ] != m.values[ j ][ i ] )
				return false;

	return true;
}

void transposeSquareMatrix( matrix* m ) {
	if ( !isSquareMatrix( *m ) )
		return;

	matrix mt = getMemMatrix( m->nCols , m->nRows );

	for ( int i = 0; i < m->nCols; ++i )
		for ( int j = 0; j < m->nCols; ++j )
			mt.values[ i ][ j ] = m->values[ j ][ i ];

	freeMemMatrix( *m );

	*m = mt;
}

position getMinValuePos( matrix m ) {
	position minValuePos = ( position ) { 0 , 0 };

	for ( int i = 0; i < m.nRows; ++i )
		for ( int j = 0; j < m.nCols; ++j )
			if ( m.values[ i ][ j ] < m.values[ minValuePos.rowIndex ][ minValuePos.colIndex ] ) {
				minValuePos.rowIndex = i;
				minValuePos.colIndex = j;
			}

	return minValuePos;
}

position getMaxValuePos( matrix m ) {
	position maxValuePos = ( position ) { 0 , 0 };

	for ( int i = 0; i < m.nRows; ++i )
		for ( int j = 0; j < m.nCols; ++j )
			if ( m.values[ i ][ j ] > m.values[ maxValuePos.rowIndex ][ maxValuePos.colIndex ] ) {
				maxValuePos.rowIndex = i;
				maxValuePos.colIndex = j;
			}

	return maxValuePos;
}

matrix createMatrixFromArray( const int* a , int nRows , int nCols ) {
	matrix m = getMemMatrix( nRows , nCols );

	int k = 0;
	for ( int i = 0; i < nRows; i++ )
		for ( int j = 0; j < nCols; j++ )
			m.values[ i ][ j ] = a[ k++ ];

	return m;
}
