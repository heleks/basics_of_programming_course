#ifndef printReversedWords_h
#define printReversedWords_h

void printReversedWords( char* string ) {
    char* copyEnd = copy( string , getEndOfString( string ) , _stringBuffer );
    *copyEnd = '\0';
    getBagOfWords( &_bag , _stringBuffer );

    char* begin = string;

    for ( int i = 0; i < _bag.size; ++i ) {
        char* reverseCopyEnd = reverseCopy( _bag.words[ i ].end - 1 , _bag.words[ i ].begin - 1 , begin );
        *reverseCopyEnd = '\0';
        printf( "%s\n" , begin );
    }
}

void test_printReversedWords( ) {
    char s[ ] = "abcdef nibba";
    printReversedWords( s );
}

#endif