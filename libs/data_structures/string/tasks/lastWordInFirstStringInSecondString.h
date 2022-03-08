#ifndef lastWordInFirstStringInSecondString_h
#define lastWordInFirstStringInSecondString_h

WordDescriptor lastWordInFirstStringInSecondString( char* s1 , char* s2 ) {
    getBagOfWords( &_bag , s1 );
    getBagOfWords( &_bag2 , s2 );

    WordDescriptor* readBagR = _bag.words + _bag.size - 1;
    WordDescriptor* readBag2 = _bag2.words;
    while ( readBagR >= _bag.words ) {
        WordDescriptor* w = readBag2;
        while ( w < _bag2.words + _bag2.size ) {
            if ( !areWordsEqual( *readBagR , *w ) )
                return *readBagR;

            ++w;
        }

        --readBagR;
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