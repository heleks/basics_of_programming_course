#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "libs/data_structures/string/string_.h"
#include "libs/data_structures/string/tasks/all_tasks.h"

int main( ) {
	char t[ 100 ] = "2b1c";
	replaceDigitsToSpaces( t );
	printf( t );
	return 0;
}
