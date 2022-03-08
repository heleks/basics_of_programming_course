#ifndef getStringFromWords_h
#define getStringFromWords_h

void getStringFromWords( char* s ) {
    WordDescriptor currentWord , lastWord;
    char* startWord = s;
    char* stringWriter = s;
    char* endBuff = copy( s , getEndOfString( s ) , _stringBuffer );
    *endBuff = '\0';

    getWordReverse( endBuff - 1 , _stringBuffer - 1 , &lastWord );
    while ( getWord( startWord , &currentWord ) ) {
        if ( areWordsEqual( lastWord , currentWord ) ) {
            stringWriter = copy( currentWord.begin , currentWord.end , stringWriter );
            *stringWriter++ = ' ';
        }
        startWord = currentWord.end;
    }

    *stringWriter = '\0';
}

void test_getStringFromWords( ) {
    char str[ ] = "abc def abc";

    getStringFromWords( str );
    ASSERT_STRING( str , "def" );
}
#endif