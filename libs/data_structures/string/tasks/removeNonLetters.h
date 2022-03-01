#ifndef removeNonLetters_h
#define removeNonLetters_h

void removeNonLetters( char* s ) {
	char* endSource = getEndOfString( s );
	char* destination = copyIf( s , endSource , s , isgraph );
	*destination = '\0';
}

void test_removeNonLetters_withoutSpace( ) {
	char s[ ] = "HelloWorld";
	removeNonLetters( s );
	ASSERT_STRING( "HelloWorld" , s );
}

void test_removeNonLetters_withSpace( ) {
	char s[ ] = "Hello World";
	removeNonLetters( s );
	ASSERT_STRING( "HelloWorld" , s );
}

void test_removeNonLetters( ) {
	test_removeNonLetters_withoutSpace( );
	test_removeNonLetters_withSpace( );
}

#endif