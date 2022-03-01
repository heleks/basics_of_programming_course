#ifndef digitToEnd_h
#define digitToEnd_h

void digitToStart( WordDescriptor word ) {
    char* endStringBuffer = copy( word.begin , word.end , _stringBuffer );
    char* recPosition = copyIfReverse( endStringBuffer - 1 , _stringBuffer - 1 , word.begin , isdigit );
    copyIf( _stringBuffer , endStringBuffer , recPosition , isalpha );
}

void digitToEnd( char* s ) {
    char* beginSearch = s;
    WordDescriptor word;
    while ( getWord( beginSearch , &word ) ) {
        char* endStringBuffer = copy( word.begin , word.end , _stringBuffer );
        char* recPosition = copyIf( _stringBuffer , endStringBuffer , word.begin , isalpha );
        copyIf( _stringBuffer , endStringBuffer , recPosition , isdigit );
        beginSearch = word.end;
    }
}

void test_digitToEnd( ) {
	char s[ ] = "123ABC";
	digitToEnd( s );
	ASSERT_STRING( "ABC123" , s );
}

#endif