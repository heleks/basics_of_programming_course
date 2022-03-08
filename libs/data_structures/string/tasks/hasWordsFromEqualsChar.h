#ifndef hasWordsFromEqualsChar_h
#define hasWordsFromEqualsChar_h

int compare_char( const void* a , const void* b ) {
    char arg1 = *( const char* )a;
    char arg2 = *( const char* )b;

    if ( arg1 < arg2 ) 
        return -1;

    if ( arg1 > arg2 ) 
        return 1;

    return 0;
}

bool hasWordsFromEqualsChar( char* s ) {
    char* endBuf = copy( s , getEndOfString( s ) , _stringBuffer );
    *endBuf = '\0';
    char* startWord = _stringBuffer;
    WordDescriptor word;

    while ( getWord( startWord , &word ) ) {
        qsort( word.begin , word.end - word.begin , sizeof( char ) , compare_char );
        startWord = word.end;
    }

    return isStringHasEqualWords( _stringBuffer );
}

void test_hasWordsFromEqualsChar( ) {
    assert( hasWordsFromEqualsChar( "aboba abbao" ) );
}

#endif