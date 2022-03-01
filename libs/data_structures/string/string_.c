#include "string_.h"

size_t strlen_( const char* begin ) {
	char* end = begin;

	while ( *end != '\0' )
		++end;

	return end - begin;
}

char* find( char* begin , char* end , int ch ) {
	while ( begin != end && *begin != ch )
		++begin;

	return begin;
}

char* findNonSpace( char* begin ) {
	while ( *begin != '\0' && isspace( *begin ) )
		++begin;

	return begin;
}

char* findSpace( char* begin ) {
	while ( *begin != '\0' && !isspace( *begin ) )
		++begin;

	return begin;
}

char* findNonSpaceReverse( char* rbegin , const char* rend ) {
	while ( rbegin != rend && isspace( *rbegin ) )
		--rbegin;

	return rbegin;
}

char* findSpaceReverse( char* rbegin , const char* rend ) {
	while ( rbegin != rend && !isspace( *rbegin ) )
		--rbegin;

	return rbegin;
}

int strcmp( const char* lhs , const char* rhs ) {
	while ( *lhs == *rhs && *lhs != '\0' )
		++lhs, ++rhs;

	return *lhs - *rhs;
}

char* copy( const char* beginSource , const char* endSource , char* beginDestination ) {
	memcpy( beginDestination , beginSource , endSource - beginSource );

	return beginDestination + ( endSource - beginSource );
}

char* copyIf( char* beginSource , const char* endSource , char* beginDestination , int ( *f )( int ) ) {
	while ( beginSource != endSource ) {
		if ( f( *beginSource ) ) {
			memcpy( beginDestination , beginSource , sizeof( char ) );
			++beginDestination;
		}

		++beginSource;
	}

	return beginDestination;
}

char* copyIfReverse( char* rbeginSource , const char* rendSource , char* beginDestination , int ( *f )( int ) ) {
	while ( rbeginSource != rendSource ) {
		if ( f( *rbeginSource ) ) {
			memcpy( beginDestination , rbeginSource , sizeof( char ) );
			++beginDestination;
		}

		--rbeginSource;
	}

	return beginDestination;
}

char* getEndOfString( char* str ) {
	while ( *str != '\0' )
		++str;

	return str;
}

void assertString( const char* expected , char* got , char const* fileName , char const* funcName , int line ) {
	if ( strcmp( expected , got ) ) {
		fprintf( stderr , " File %s\n" , fileName );
		fprintf( stderr , "%s - failed on line %d\n" , funcName , line );
		fprintf( stderr , " Expected : \"%s\"\n" , expected );
		fprintf( stderr , "Got: \"%s\"\n\n" , got );
	}
	else
		fprintf( stderr , "%s - OK\n" , funcName );
}

bool getWord( char* beginSearch , WordDescriptor* word ) {
	word->begin = findNonSpace( beginSearch );
	if ( *word->begin == '\0' )
		return false;

	word->end = findSpace( word->begin );

	return true;
}

bool getWordReverse( char* rbegin , char* rend , WordDescriptor* word ) {
	word->end = findNonSpaceReverse( rbegin , rend );
	if ( *word->end == '\0' )
		return false;

	word->begin = findSpaceReverse( word->end , rend );

	return true;
}

int charToDigit( char x ) {
	return x - '0';
}