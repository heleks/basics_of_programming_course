#ifndef isOrderedString_h
#define isOrderedString_h

int isOrderedString( char* beginString ) {
    WordDescriptor previousWord , currentWord;

    getWord( beginString , &previousWord );
    beginString = previousWord.end;

    while ( getWord( beginString , &currentWord ) ) {
        if ( areWordsEqual( previousWord , currentWord ) )
            return false;
        else {
            previousWord = currentWord;
            beginString = currentWord.end;
        }

    }

    return true;
}

void test_isOrderedString( ) {
    char s[ ] = "1 2 3";

    assert( isOrderedString( s ) == true );
}


#endif