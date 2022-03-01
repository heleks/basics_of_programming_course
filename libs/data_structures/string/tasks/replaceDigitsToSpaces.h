#ifndef replaceDigitsToSpaces_h
#define replaceDigitsToSpaces_h

void replaceDigitsToSpaces( char* s ) {
    copy( s , getEndOfString( s ) , _stringBuffer );
    int len = 0;

    for ( int i = 0; i < strlen_( _stringBuffer ); ++i ) {
        char symbol = *( _stringBuffer + i );

        if ( isdigit( symbol ) ) {
            for ( int i = 0; i < getDigit( symbol ); ++i )
                *( s + len++ ) = ' ';
        }
        else
            *( s + len++ ) = symbol;
    }

    *( s + len ) = '\0';
}

void test_replaceDigitsToSpaces( ) {
    char s[ MAX_STRING_SIZE ] = "3c1z0b1a";
    replaceDigitsToSpaces( s );
    ASSERT_STRING( "   c zb a" , s );
}

#endif