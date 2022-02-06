#include "vector.h"

vector createVector( size_t n ) {
	int* v = ( int* )malloc( sizeof( int ) * n );

	if ( v == NULL ) {
		fprintf( stderr , "bad alloc" );
		exit( 1 );
	}

	return ( vector ) { v , 0 , n };
}

void reserve( vector* v , size_t newCapacity ) {
	if ( newCapacity == 0 )
		v->data = NULL;
	else if ( v->size > newCapacity )
		v->size = newCapacity;

	if ( ( v->data = ( int* )realloc( v->data , sizeof( int ) * newCapacity ) ) != NULL )
		v->capacity = newCapacity;
	else {
		fprintf( stderr , "bad alloc" );
		exit( 1 );
	}
}

void clear( vector* v ) {
	v->size = 0;
}

void shrinkToFit( vector* v ) {
	reserve( v , v->size );
}

void deleteVector( vector* v ) {
	free( v->data );
}

bool isEmpty( vector* v ) {
	return v->size == 0;
}

bool isFull( vector* v ) {
	return v->size == v->capacity;
}

int getVectorValue( vector* v , size_t i ) {
	return v->data[ i ];
}

void pushBack( vector* v , int x ) {
	if ( isEmpty( v ) && isFull( v ) )
		reserve( v , 1 );
	else if ( isFull( v ) )
		reserve( v , 2 * v->capacity );

	v->data[ v->size ] = x;
	++v->size;
}

void popBack( vector* v ) {
	if ( isEmpty( v ) ) {
		fprintf( stderr , "vector is empty" );
		exit( 1 );
	}
	
	v->size--;
}
