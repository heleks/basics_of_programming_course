#ifndef lastWordInFirstStringInSecondString_h
#define lastWordInFirstStringInSecondString_h

WordDescriptor lastWordInFirstStringInSecondString( char* s1 , char* s2 ) {
    getBagOfWords( &_bag , s1 );
    getBagOfWords( &_bag2 , s2 );

    WordDescriptor* wordBegin = _bag2.words;
    WordDescriptor* wordEnd = _bag.words + _bag.size - 1;

    while ( _bag.words <= wordEnd ) {
        WordDescriptor* w = wordBegin;
        while ( w < _bag2.words + _bag2.size ) {
            if ( !areWordsEqual( *wordEnd , *w ) )
                return *wordEnd;

            ++w;
        }

        --wordEnd;
    }

    return (WordDescriptor){ 0 , 0 };
}

void test_lastWordInFirstStringInSecondString( ) {
    char s1[ ] = "4";
    char s2[ ] = "1 2 3 4 5 6";
    WordDescriptor word = lastWordInFirstStringInSecondString( s1 , s2 );

    char res[ MAX_STRING_SIZE ];
    wordDescriptorToString( word , res );
    ASSERT_STRING( "4" , res );
}

#endif