#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "libs/data_structures/vector/vector.h"

void test_pushBack_emptyVector( ) {
    vector v = createVector( 0 );
    pushBack( &v , 0 );

    assert( v.capacity == 1 );
}

void test_pushBack_fullVector( ) {
    vector v = createVector( 1 );
    pushBack( &v , 0 );
    pushBack( &v , 1 );
    pushBack( &v , 2 );

    assert( v.capacity == 4 );
}

void test_popBack_notEmptyVector( ) {
    vector v = createVector( 0 );
    pushBack( &v , 10 );

    assert( v.size == 1 );

    popBack( &v );

    assert( v.size == 0 );
    assert( v.capacity == 1 );
}

void test( ) {
    test_pushBack_emptyVector( );
    test_pushBack_fullVector( );
    test_popBack_notEmptyVector( );
}

int main( ) {
	vector v = createVector( 0 );

    test( );

	return 0;
}
