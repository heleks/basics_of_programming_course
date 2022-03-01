#ifndef removeNonLetters_h
#define removeNonLetters_h

void removeNonLetters( char* s ) {
	char* endSource = getEndOfString( s );
	char* destination = copyIf( s , endSource , s , isgraph );
	*destination = '\0';
}

#endif