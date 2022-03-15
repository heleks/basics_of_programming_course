#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <time.h> 
#include <stdint.h> 
#include <memory.h> 
#include "sorts.h"

#define TIME_TEST(testCode, time){ \
    clock_t start_time = clock();     \
    testCode                          \
    clock_t end_time = clock();        \
    clock_t sort_time = end_time - start_time; \
    time = (double) sort_time / CLOCKS_PER_SEC;\
    }

#define ARRAY_SIZE(a) sizeof a / sizeof a[0]

typedef struct sortFunc {
    void ( *sort )( int* , size_t );

    char name[ 64 ];
} sortFunc;

typedef struct generatingFunc {
    void ( *generate )( int* , size_t );

    char name[ 64 ];
} generatingFunc;

void swap( void* a , void* b , size_t size ) { 
    char* buffer = ( char* )malloc( size );

    if ( buffer ) { 
        memmove( buffer , a , size ); 
        memmove( a , b , size ); 
        memmove( b , buffer , size ); 
        free( buffer ); 
    } 
}

bool isOrdered( int* a , size_t size ) {
    for ( int i = 0; i < size - 1; ++i )
        if ( a[ i + 1 ] < a[ i ] )
            return false;

    return true;
}

void outputArray( int* a , int size ) {
    for ( int i = 0; i < size; ++i )
        printf( "%d " , a[ i ] );
}

int compare( const void* a , const void* b ) {
    return *( int* )a - *( int* )b;
}

void generateRandomArray( int* a , size_t size ) {
    srand( time( 0 ) );

    for ( int i = 0; i < size; ++i )
        a[ i ] = rand( ) % 1000;
}

void generateOrderedArray( int* a , size_t size ) {
    srand( time( 0 ) );
    for ( int i = 0; i < size; ++i )
        a[ i ] = rand( ) % 1000;
    
    qsort( a , size , sizeof a[ 0 ] , compare );
}

int compareBackwards( const void* a , const void* b ) {
    return *( int* )b - *( int* )a;
}

void generateOrderedBackwards( int* a , size_t size ) {
    srand( time( 0 ) );

    for ( int i = 0; i < size; ++i )
        a[ i ] = rand( ) % 1000;

    qsort( a , size , sizeof a[ 0 ] , compareBackwards );
}

void bubbleSort( int* a , int size ) {
    int k = 0;
    for ( int i = 0; i < size; ++i ) {
        bool flag = false;
        for ( int j = 1; j < size - k; ++j )
            if ( a[ j ] < a[ j - 1 ] ) {
                swap( a + j , a + j - 1 , sizeof a[ j ] );
                flag = true;
            }    

        if ( !flag )
            break;

        ++k;
    }
}

void selectionSort( int* a , int size ) {
    for ( int i = 0; i < size - 1; ++i ) {
        int minPos = i;

        for ( int j = i + 1; j < size; ++j )
            if ( a[ j ] < a[ minPos ] )
                minPos = j;
        swap( a + i , a + minPos , sizeof a[ minPos ] );
    }
}
