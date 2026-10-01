#ifndef H_DSA
#define H_DSA

#include <stddef.h>

typedef struct vector vector_t;

vector_t* vector_create(size_t elem_size, size_t capacity);

#endif // H_DSA
