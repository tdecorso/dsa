#include "dsa.h"
#include "error.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

static void mark_ok(dsa_error_t* err) {
    format_error(err, DSA_ERROR_OKAY, "");
}

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

    mark_ok(err);

    return v;
}

void vector_destroy(dsa_vector_t* v) {
    if (!v) return;
    free(v->data);
    free(v);
}

void vector_push_back(dsa_vector_t* v, void* item, dsa_error_t* err) {
    if (!v) {
        format_error(err, DSA_ERROR_INVALID_ARGS, "You cannot push back an item to a NULL vector.");
        return;
    }

    if (!item) {
        format_error(err, DSA_ERROR_INVALID_ARGS, "You cannot push back a NULL item.");
        return;
    }

    if (v->count == v->capacity) {
        size_t resized = v->capacity * 2;
        void* ndata = realloc(v->data, resized);
        if (!ndata) {
            format_error(err, DSA_ERROR_MEMORY_FAIL, "Could not resize the vector.");
            return;
        }
        v->data = ndata;
        v->capacity = resized;
    }

    uint8_t* base = v->data;
    memcpy(base + v->count * v->elemsz, item, v->elemsz);
    mark_ok(err);
}

size_t vector_count(const dsa_vector_t* v) {
    return v ? v->count : 0;
}

size_t vector_elem_size(const dsa_vector_t* v) {
    return v ? v->elemsz : 0;
}

size_t vector_capacity(const dsa_vector_t* v) {
    return v ? v->capacity : 0;
}

void* vector_data(const dsa_vector_t* v) {
    return v ? v->data : NULL;
}
