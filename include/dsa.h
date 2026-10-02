#ifndef H_DSA
#define H_DSA

#include <stddef.h>

typedef enum error_type {
    DSA_ERROR_INVALID_ARGS,
    DSA_ERROR_MEMORY_FAIL,
} dsa_error_type_t;

typedef struct error dsa_error_t;
typedef struct vector dsa_vector_t;

dsa_vector_t* vector_create(size_t elem_size, size_t capacity, dsa_error_t* err);

void vector_destroy(dsa_vector_t* v);

#endif // H_DSA
