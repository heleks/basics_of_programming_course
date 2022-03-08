#ifndef getWordsReversed_h
#define getWordsReversed_h

void getWordsReversed( char* s ) {
    char* end = copy( s , getEndOfString( s ) , _stringBuffer );
    char* begin = s;
    char* beginSearch = end - 1;
    WordDescriptor word;

    while ( getWordReverse( beginSearch , _stringBuffer - 1 , &word ) ) {
        begin = copy( word.begin , word.end , begin );
        *begin++ = ' ';

        char* startNextWord = beginSearch - word.end + word.begin - 1;
        beginSearch = findNonSpaceReverse( startNextWord , _stringBuffer - 1 );
    }

    *begin = '\0';
}

void test_getWordsReversed( ) {
    char s[ 20 ] = "Hello World";
    getWordsReversed( s );
    ASSERT_STRING( "World Hello" , s );
}

#endif