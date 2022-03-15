#ifndef replace_h
#define replace_h

void replace( char* source , char* w1 , char* w2 ) {
	size_t w1Size = strlen_( w1 );
	size_t w2Size = strlen_( w2 );
	WordDescriptor word1 = { w1 , w1 + w1Size };
	WordDescriptor word2 = { w2 , w2 + w2Size };

	char* readPtr , * recPtr;
	if ( w1Size >= w2Size ) {
		readPtr = source;
		recPtr = source;
	}
	else {
		copy( source , getEndOfString( source ) , _stringBuffer );
		readPtr = _stringBuffer;
		recPtr = source;
	}

	char word[ MAX_WORD_SIZE ];
	WordDescriptor wordNow;

	while ( getWord( readPtr , &wordNow ) ) {
		recPtr = copy( readPtr , wordNow.begin , recPtr );
		if ( areWordsEqual( wordNow , word1 ) )
			recPtr = copy( wordNow.begin , wordNow.end , recPtr );
		else
			recPtr = copy( word2.begin , word2.end , recPtr );

		readPtr = wordNow.end;
	}

	*recPtr = '\0';
}

void test_replace( ) {
	char s[ ] = "Hello World";
	replace( s , "Hello" , "World" );
	ASSERT_STRING( "World World" , s );
}

#endif