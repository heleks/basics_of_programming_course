#ifndef string_h
#define string_h

#include <stdint.h>
#include <ctype.h>
#include <memory.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_STRING_SIZE 100
#define MAX_N_WORDS_IN_STRING 100
#define MAX_WORD_SIZE 20

char _stringBuffer[ MAX_STRING_SIZE + 1 ];

#define ASSERT_STRING(expected, got) assertString(expected, got, __FILE__, __FUNCTION__, __LINE__)

size_t strlen_( const char* begin );

char* find( char* begin , char* end , int ch );

char* findNonSpace( char* begin );

char* findSpace( char* begin );

char* findComma( char* begin );

char* findNonComma( char* begin );

char* findNonSpaceReverse( char* rbegin , const char* rend );

char* findSpaceReverse( char* rbegin , const char* rend );

int strcmp( const char* lhs , const char* rhs );

char* copy( const char* beginSource , const char* endSource , char* beginDestination );

char* reverseCopy( char* rbeginSource , const char* rendSource , char* beginDestination );

char* copyIf( char* beginSource , const char* endSource , char* beginDestination , int( *f )( int ) );

char* copyIfReverse( char* rbeginSource , const char* rendSource , char* beginDestination , int( *f )( int ) );

char* getEndOfString( char* str );

void assertString( const char* expected , char* got , char const* fileName , char const* funcName , int line );

typedef struct WordDescriptor {
	char* begin;
	char* end;
} WordDescriptor;

bool getWord( char* beginSearch , WordDescriptor* word );

bool getWordComma( char* beginSearch , WordDescriptor* word );

bool getWordReverse( char* rbegin , char* rend , WordDescriptor* word );

int getDigit( char x );

bool areWordsEqual( WordDescriptor w1 , WordDescriptor w2 );

typedef struct BagOfWords {
	WordDescriptor words[ MAX_N_WORDS_IN_STRING ];
	size_t size;
} BagOfWords;

BagOfWords _bag;
BagOfWords _bag2;

void getBagOfWords( BagOfWords* bag , char* s );

void wordDescriptorToString( WordDescriptor word , char* destination );

typedef enum WordBeforeFirstWordWithAReturnCode {
	FIRST_WORD_WITH_A ,
	NOT_FOUND_A_WORD_WITH_A ,
	WORD_FOUND ,
	EMPTY_STRING
} WordBeforeFirstWordWithAReturnCode;

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA( char* s , char** beginWordBefore , char** endWordBefore );

#endif