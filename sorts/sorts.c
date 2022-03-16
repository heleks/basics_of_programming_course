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

void insertionSort( int* a , int size ) {
    for ( int i = 1; i < size; ++i ) {
        int j = i;
        while ( j > 0 && a[ j - 1 ] > a[ j ] ) {
            swap( a + j , a + j - 1 , sizeof a[ j ] );
            --j;
        }
    }
}

void combSort( int* a , int size ) {
    int step = size;
    double factor = 1.24733;
    bool swapped = false;
    while ( step > 1 || swapped ) {
        swapped = false;
        if ( step > 1 )
            step /= factor;
        
        for ( int i = 0 , j = i + step; j < size; ++j , ++i ) 
            if ( a[ i ] > a[ j ] ) {
                swap( a + i , a + j , sizeof a[ i ] );
                swapped = true;
            }
    }
}

void shellSort( int* a , int size ) {
    for ( int gap = size / 2; gap > 0; gap /= 2 ) {
        for ( int i = gap; i < size; ++i ) {
            int j = i;
            while ( j >= gap && a[ j ] < a[ j - gap ] ) {
                swap( a + j , a + j - gap , sizeof a[ j ] );
                j -= gap;
            }
        }
    }
}

int getMax( int* a , int size ) {
    int index = 0;

    for ( int i = 1; i < size; ++i )
        if ( a[ i ] > a[ index ] )
            index = i;

    return a[ index ];
}

void countingSort( int* a , int size ) {
    int* copyOfArray = ( int* )malloc( sizeof( int ) * size );
    memmove( copyOfArray , a , sizeof( int ) * size );

    int sizeOfIndexArray = getMax( a , size ) + 1;
    int* indexArray = ( int* )malloc( sizeof( int ) * sizeOfIndexArray );
    memset( indexArray , 0 , sizeof( int ) * sizeOfIndexArray );

    for ( int i = 0; i < size; ++i )
        ++indexArray[ a[ i ] ];
    
    for ( int i = 1; i < sizeOfIndexArray; ++i )
        indexArray[ i ] += indexArray[ i - 1 ];
    
    for ( int i = 0; i < size; ++i ) {
        a[ indexArray[ copyOfArray[ i ] ] - 1 ] = copyOfArray[ i ];
        --indexArray[ copyOfArray[ i ] ];
    }

    free( copyOfArray );
    free( indexArray );
}


int digit( int n , int k , int N , int M ) {
    return ( n >> ( N * k ) & ( M - 1 ) );
}

void _radixSort( int* l , int* r , int N ) {
    int k = ( 32 + N - 1 ) / N;
    int M = 1 << N;
    int sz = r - l;
    int* b = ( int* )malloc( sizeof( int ) * sz );
    int* c = ( int* )malloc( sizeof( int ) * M );

    for ( int i = 0; i < k; i++ ) {
        for ( int j = 0; j < M; j++ ) 
            c[ j ] = 0;

        for ( int* j = l; j < r; j++ ) 
            c[ digit( *j , i , N , M ) ]++;

        for ( int j = 1; j < M; j++ ) 
            c[ j ] += c[ j - 1 ];

        for ( int* j = r - 1; j >= l; j-- ) 
            b[ --c[ digit( *j , i , N , M ) ] ] = *j;

        int cur = 0;

        for ( int* j = l; j < r; j++ ) 
            *j = b[ cur++ ];
    }

    free( b );
    free( c );
}

void radixSort( int* a , size_t n ) {
    _radixSort( a , a + n , 8 );
}

long long getSelectionSortNComps( int* a , int size ) {
    long long nComps = 0;

    for ( int i = 0; ++nComps && i < size - 1; ++i ) {
        int min = i;
        for ( int j = i + 1; ++nComps && j < size; ++j ) {
            if ( a[ j ] < a[ min ] )
                min = j;
            
            ++nComps;
        }

        swap( a + i , a + min , sizeof a[ 0 ] );
        ++nComps;
    }

    return nComps;
}

long long getBubbleSortNComp( int* a , int size ) {
    long long nComp = 0;
    bool flag = false;
    int k = 0;

    for ( int i = 0; ++nComp && i < size; ++i ) {
        for ( int j = 1; ++nComp && j < size - k; ++j ) {
            if ( a[ j ] < a[ j - 1 ] ) {
                swap( a + j , a + j - 1 , sizeof a[ 0 ] );
                flag = true;
                ++nComp;
            }
            ++nComp;
        }

        if ( !flag ) {
            break;

        }
        ++k;
    }

    return nComp;
}

long long getInsertionSortNComps( int* a , int size ) {
    long long nComp = 0;

    for ( int i = 1; ++nComp && i < size; ++i ) {
        int j = i;
        while ( ++nComp && j > 0 && a[ j ] < a[ j - 1 ] ) {
            swap( a + j , a + j - 1 , sizeof a[ 0 ] );
            nComp += 2;
            --j;
        }
    }

    return nComp;
}
long long getCombSortNComps( int* a , int size ) {
    double factor = 1.24733;
    int step = size;
    bool swapped;
    long long nComp = 0;
    while ( ++nComp && step > 1 || swapped ) {
        if ( factor > 1 )
            step /= factor;
        
        ++nComp;
        swapped = false;
        for ( int i = 0 , j = i + step; ++nComp && j < size; ++i , ++j ) {
            if ( a[ j ] < a[ i ] ) {
                swap( a + j , a + i , sizeof a[ 0 ] );
                ++nComp;
                swapped = true;
            }

            ++nComp;
        }
    }

    return nComp;
}

long long getShellSortNComps( int* a , int size ) {
    long long nComps = 0;
    for ( int gap = size / 2; ++nComps && gap > 0; gap /= 2 ) {
        for ( int i = gap; ++nComps && i < size; ++i ) {
            int j = i;
            while ( ++nComps && j >= gap && a[ j ] < a[ j - gap ] ) {
                swap( a + j , a + j - gap , sizeof a[ 0 ] );
                nComps += 2;
                j -= gap;
            }
        }
    }

    return nComps;
}

long long getCountingSortNComps( int* a , int size ) {
    int* copyOfArray = ( int* )malloc( sizeof( int ) * size );
    memmove( copyOfArray , a , sizeof( int ) * size );

    int sizeOfIndexArray = getMax( a , size ) + 1;
    int* indexArray = ( int* )malloc( sizeof( int ) * sizeOfIndexArray );
    memset( indexArray , 0 , sizeof( int ) * sizeOfIndexArray );

    long long nComp = 3 * size;
    for ( int i = 0; ++nComp && i < size; ++i )
        ++indexArray[ a[ i ] ];
    
    for ( int i = 1; ++nComp && i < sizeOfIndexArray; ++i )
        indexArray[ i ] += indexArray[ i - 1 ];
    
    for ( int i = 0; ++nComp && i < size; ++i ) {
        a[ indexArray[ copyOfArray[ i ] ] - 1 ] = copyOfArray[ i ];
        --indexArray[ copyOfArray[ i ] ];
    }

    free( copyOfArray );
    free( indexArray );

    return nComp;
}

long long _getRadixSort( int* l , int* r , int N ) {
    long long nComp = 0;
    int k = ( 32 + N - 1 ) / N;
    int M = 1 << N;
    int sz = r - l;
    int* b = ( int* )malloc( sizeof( int ) * sz );
    int* c = ( int* )malloc( sizeof( int ) * M );

    for ( int i = 0; ++nComp && i < k; i++ ) {
        for ( int j = 0; ++nComp && j < M; j++ ) 
            c[ j ] = 0;

        for ( int* j = l; ++nComp && j < r; j++ ) 
            c[ digit( *j , i , N , M ) ]++;

        for ( int j = 1; ++nComp && j < M; j++ ) 
            c[ j ] += c[ j - 1 ];

        for ( int* j = r - 1; ++nComp && j >= l; j-- ) 
            b[ --c[ digit( *j , i , N , M ) ] ] = *j;

        int cur = 0;

        for ( int* j = l; ++nComp && j < r; j++ ) 
            *j = b[ cur++ ];
    }

    free( b );
    free( c );

    return nComp;
}

long long getRadixSortNComp( int* a , size_t n ) {
    return _getRadixSort( a , a + n , 8 );
}

void checkTime( void( *sortFunc )( int* , size_t ) , void( *generateFunc )( int* , size_t ) , size_t size , char* experimentName ) {
    static size_t runCounter = 1;
    static int innerBuffer[ 100000 ];
    generateFunc( innerBuffer , size );
    printf( "Run #%zu | " , runCounter++ );

    printf( "Name : %s\n" , experimentName );
    double time;
    TIME_TEST( { sortFunc( innerBuffer, size ); } , time ) 
        printf( "Status: " );

        if ( isOrdered( innerBuffer , size ) ) {
            printf( "OK! Time: %.3f s.\n" , time );
            char* filename[ 256 ];
            sprintf( filename , "%s.csv" , experimentName );
            FILE* f = fopen( filename , "a" );

            if ( f == NULL ) {
                printf( "An error occurred when opening the file %s" , filename );
                exit( 1 );
            }

            fprintf( f , "%zu; %.3f\n" , size , time );
            fclose( f );
        }
        else {
            printf( "Wrong!\n" );
            outputArray( innerBuffer , size );
            exit( 1 );
        }
}

void doit( ) {
    sortFunc sorts[ ] = {

      {
        radixSort,
        "radixSort"
      }
    };

    const unsigned numberOfFunc = ARRAY_SIZE( sorts );

    generatingFunc generatingFuncs[ ] = {
      {
        generateRandomArray,
        "random"
      },
      {
        generateOrderedArray,
        "ordered"
      },
      {
        generateOrderedBackwards,
        "orderedBackwards"
      }
    };

    const unsigned numberOfGeneratingFuncs = ARRAY_SIZE( generatingFuncs );
    for ( size_t size = 150000; size <= 190000; size += 10000 ) {
        printf( "--------------------------------- \n" );
        printf( "Size: %u\n" , size );

        for ( int i = 0; i < numberOfFunc; ++i ) {
            for ( int j = 0; j < numberOfGeneratingFuncs; ++j ) {
                static char filename[ 128 ];
                sprintf( filename , "%s_%s_time" , sorts[ i ].name , generatingFuncs[ j ].name );
                checkTime( sorts[ i ].sort , generatingFuncs[ j ].generate , size , filename );
            }
        }

        printf( "\n" );
    }
}