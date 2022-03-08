#ifndef getWordBeforeFirstWordWithA_h
#define getWordBeforeFirstWordWithA_h
WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA( char* s , char** beginWordBefore , char** endWordBefore ) {
	char* begin = s;
	WordDescriptor word;

	getBagOfWords( &_bag , begin );

	if ( !getWord( s , &word ) )
		return EMPTY_STRING;

	if ( find( _bag.words[ 0 ].begin , _bag.words[ 0 ].end , 'a' ) != _bag.words[ 0 ].end || find( _bag.words[ 0 ].begin , _bag.words[ 0 ].end , 'A' ) != _bag.words[ 0 ].end )
		return FIRST_WORD_WITH_A;

	for ( int i = 1; i < _bag.size; i++ ) {

		if ( find( _bag.words[ i ].begin , _bag.words[ i ].end , 'a' ) != _bag.words[ i ].end || find( _bag.words[ i ].begin , _bag.words[ i ].end , 'A' ) != _bag.words[ i ].end ) {
			*beginWordBefore = _bag.words[ i - 1 ].begin;
			*endWordBefore = _bag.words[ i - 1 ].end;

			return WORD_FOUND;
		}
	}

	return NOT_FOUND_A_WORD_WITH_A;
}

void testAll_getWordBeforeFirstWordWithA( ) {
	char* beginWord , * endWord;

	char s1[ ] = "";
	assert( getWordBeforeFirstWordWithA( s1 , &beginWord , &endWord ) == EMPTY_STRING );

	char s2[ ] = " ABC";
	assert( getWordBeforeFirstWordWithA( s2 , &beginWord , &endWord ) == FIRST_WORD_WITH_A );

	char s3[ ] = "BC A";
	assert( getWordBeforeFirstWordWithA( s3 , &beginWord , &endWord ) == WORD_FOUND );
	char got[ MAX_WORD_SIZE ];
	copy( beginWord , endWord , got );
	got[ endWord - beginWord ] = '\0';
	ASSERT_STRING( "BC" , got );

	char s4[ ] = "B Q WE YR OW IUWR ";
	assert( getWordBeforeFirstWordWithA( s4 , &beginWord , &endWord ) == NOT_FOUND_A_WORD_WITH_A );
}
#endif