#ifndef isStringHasEqualWords_h
#define isStringHasEqualWords_h

bool isStringHasEqualWords( char* s ) {
    getBagOfWords( &_bag , s );

    WordDescriptor* wordBegin = _bag.words;
    WordDescriptor* wordEnd = _bag.words + _bag.size - 1;

    while ( wordBegin < wordEnd ) {
        WordDescriptor* w = wordBegin + 1;
        while ( w <= wordEnd ) {
            if ( areWordsEqual( *wordBegin , *w ) )
                return true;

            ++w;
        }

        ++wordBegin;
    }
    return false;

}

void test_isStringHasEqualWords1( ) {
    char s[ MAX_STRING_SIZE ] = "123 123";
    assert( isStringHasEqualWords( s ) == true );
}

void test_isStringHasEqualWords2( ) {
    char s[ MAX_STRING_SIZE ] = "123 124";
    assert( isStringHasEqualWords( s ) == false );
}

#endif