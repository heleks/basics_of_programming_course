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

void test_atVector_notEmptyVector1( ) {
    vector v = createVector( 1 );
    pushBack( &v , 0 );

    assert( v.data == atVector( v , 0 ) );
}

void test_atVector_notEmptyVector2( ) {
    vector v = createVector( 2 );
    pushBack( &v , 0 );
    pushBack( &v , 1 );

    assert( v.data + 1 == atVector( v , 1 ) );
}

void test_back_oneElementInVector( ) {
    vector v = createVector( 2 );
    pushBack( &v , 0 );
    pushBack( &v , 1 );

    assert( v.data[ v.size - 1 ] == back( v ) );
}

void test_front_oneElementInVector( ) {
    vector v = createVector( 1 );
    pushBack( &v , 0 );

    assert( v.data[ v.size - 1 ] == front( v ) );
}

void test( ) {
    test_pushBack_emptyVector( );
    test_pushBack_fullVector( );
    test_popBack_notEmptyVector( );
    test_atVector_notEmptyVector1( );
    test_atVector_notEmptyVector2( );
    test_back_oneElementInVector( );
    test_front_oneElementInVector( );
}

int main( ) {
	vector v = createVector( 0 );

    test( );

	return 0;
}
