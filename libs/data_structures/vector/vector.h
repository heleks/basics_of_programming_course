#ifndef vector_h
#define vector_h

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct vector {
	int* data;
	size_t size;
	size_t capacity;
} vector;

vector createVector( size_t n );

#endif