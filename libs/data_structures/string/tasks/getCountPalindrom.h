#ifndef getCountPalindrom_h
#define getCountPalindrom_h

bool isPalindrome( WordDescriptor word ) {
    --word.end;
    int len = word.end - word.begin;

    if ( len % 2 == 0 )
        return false;

    for ( int i = 0; i < len; ++i )
        if ( *word.begin != *word.end )
            return false;
        else {
            ++word.begin;
            --word.end;
        }

    return true;
}

int getCountPalindromes( char* beginString ) {
    int result = 0;
    WordDescriptor word;;

    while ( getWordComma( beginString , &word ) ) {
        result += isPalindrome( word );

        beginString = word.end;
    }

    return result;
}

void test_getCountPalindromes_Palindrome( ) {
    char s[ ] = "aroora,abba";
    assert( 2 == getCountPalindromes( s ) );
}



#endif