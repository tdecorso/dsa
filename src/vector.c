#include "dsa.h"
#include "error.h"
#include <stdlib.h>

struct vector {
    void* data;
    size_t count;
    size_t capacity;
    size_t elemsz;
};

dsa_vector_t* vector_create(size_t elem_size, size_t capacity, dsa_error_t* err) {
    if (elem_size == 0) {
        format_error(err, DSA_ERROR_INVALID_ARGS, "Element size cannot be zero.");
        return NULL;
    }
    if (capacity == 0) capacity = 4;

    dsa_vector_t* v = malloc(sizeof(dsa_vector_t));
    if (!v) {
        format_error(err, DSA_ERROR_MEMORY_FAIL, "Could not allocate memory for the vector.");
        return NULL;
    }

    void* data = malloc(elem_size * capacity);
    if (!data) {
        format_error(err, DSA_ERROR_MEMORY_FAIL, "Could not allocate memory for the vector's data.");
        free(v);
        return NULL;
    }

    v->data = data;
    v->count = 0;
    v->capacity = capacity;
    v->elemsz = elem_size;
    return v;
}

void vector_destroy(dsa_vector_t* v) {
    if (!v) return;
    free(v->data);
    free(v);
}
