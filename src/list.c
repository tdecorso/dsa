#include "dsa.h"
#include <stdlib.h>
#include "error.h"

struct list_node {
    void *data;
    dsa_list_node_t* next;
    dsa_list_node_t* prev;
};

struct list {
    dsa_list_node_t* root;
    dsa_list_node_t* tail;
    size_t elemsz;
    size_t count;
};

static dsa_list_node_t* node_create(size_t elemsz) {
    dsa_list_node_t* n = malloc(sizeof(dsa_list_node_t));
    if (!n) return NULL;
    n->data = malloc(elemsz);
    if (!n->data) {
        free(n);
        return NULL;
    }
    n->next = NULL;
    n->prev = NULL;
    return n;
}

dsa_list_t* list_create(size_t elem_size, dsa_error_t* err) {
    if (elem_size == 0) {
        format_error(err, DSA_ERROR_INVALID_ARGS, "Element size cannot be zero.");
        return NULL;
    }
    dsa_list_t* l = malloc(sizeof(dsa_list_t));
    if (!l) {
        format_error(err, DSA_ERROR_MEMORY_FAIL, "Could not allocate memory.");
        return NULL;
    }

    l->root = node_create(elem_size);
    if (!l->root) {
        format_error(err, DSA_ERROR_MEMORY_FAIL, "Could not allocate memory.");
        free(l);
        return NULL;
    }
    l->tail = l->root;
    l->count = 0;
    l->elemsz = elem_size;
    return l;
}

static void node_destroy(dsa_list_node_t* node) {
    free(node->data);
    free(node);
}

void list_destroy(dsa_list_t* l) {
    if (!l) return;
    dsa_list_node_t* iter = l->root;
    while (iter) {
        dsa_list_node_t* next = iter->next;
        node_destroy(iter);
        iter = next;
    }
    free(l);
}
