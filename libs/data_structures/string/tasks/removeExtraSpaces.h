#ifndef removeExtraSpaces_h
#define removeExtraSpaces_h

void removeExtraSpaces( char* s ) {
    char* current = s;
    char* next = s + 1;

    while ( next != getEndOfString( s ) ) {
        if ( !isspace( *next ) || !isspace( *current ) )
            *( ++current ) = *next;

        ++next;
    }

    *( current + 1 ) = '\0';
}

void test_removeExtraSpaces( ) {
	char s[ ] = "    Hello      World   ";
	removeExtraSpaces( s );
    ASSERT_STRING( " Hello World " , s );
}

#endif