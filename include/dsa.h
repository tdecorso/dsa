#ifndef H_DSA
#define H_DSA

#ifndef DSA_ERROR_MAX_LEN
#define DSA_ERROR_MAX_LEN 128
#endif

#include <stddef.h>

typedef enum error_type {
    DSA_ERROR_OKAY,
    DSA_ERROR_INVALID_ARGS,
    DSA_ERROR_MEMORY_FAIL,
} dsa_error_type_t;

typedef struct error {
    dsa_error_type_t type;
    char msg[DSA_ERROR_MAX_LEN];
} dsa_error_t;

typedef struct vector dsa_vector_t;

dsa_vector_t* vector_create(size_t elem_size, size_t capacity, dsa_error_t* err);
void          vector_destroy(dsa_vector_t* v);

void vector_push_back(dsa_vector_t* v, void* item, dsa_error_t* err);

void*  vector_data(const dsa_vector_t* v);
size_t vector_count(const dsa_vector_t* v);
size_t vector_elem_size(const dsa_vector_t* v);
size_t vector_capacity(const dsa_vector_t* v);

#endif // H_DSA
