#include "dsa.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>

static int g_total = 0;
static int g_failed = 0;

static void check(bool eq, const char* fmt, ...) {
    g_total++;
    if (!eq) {
        g_failed++;
        va_list args;
        va_start(args, fmt);
        vfprintf(stderr, fmt, args);
        va_end(args);
    }
}

static void summary() {
    fprintf(stdout, "\nTests passed: %d/%d\n\n", g_total-g_failed, g_total);
}

void test_vector_create() {
    dsa_vector_t* v = vector_create(sizeof(int), 10, NULL);
    check(v != NULL, "\nvector_create: valid arguments return NULL.\n");
    vector_destroy(v);
}

void test_vector_push_back() {
    dsa_vector_t* v = vector_create(sizeof(int), 10, NULL);
    dsa_error_t error = {0};
    int some = 1;
    vector_push_back(v, &some, &error);
    check(error.type == DSA_ERROR_OKAY, "\nvector_push_back: valid arguments failed.\n");
    vector_destroy(v);
}

void test_vector_pop_back() {
    dsa_vector_t* v = vector_create(sizeof(int), 10, NULL);
    dsa_error_t error = {0};
    int some = 1;
    vector_push_back(v, &some, &error);
    int another = 0;
    vector_pop_back(v, &another, NULL);
    check(some == another, "\nvector_pop_back: expected %d, got %d.\n", some, another);
    check(vector_count(v) == 0, "\nvector_pop_back: count did not decrement.\n");
    vector_destroy(v);
}

void test_vector_insert() {
    dsa_vector_t* v = vector_create(sizeof(int), 10, NULL);
    int a = 1, b = 2, c = 3;
    vector_push_back(v, &a, NULL);
    vector_push_back(v, &b, NULL);
    vector_push_back(v, &c, NULL); // [1, 2, 3]

    int x = 9;
    vector_insert(v, &x, 1, NULL); // [1, 9, 2, 3]

    int* numbers = vector_data(v);
    check(numbers[0] == 1, "\nvector_insert: expected %d, got %d\n", 1, numbers[0]);
    check(numbers[1] == 9, "\nvector_insert: expected %d, got %d\n", 9, numbers[1]);
    check(numbers[2] == 2, "\nvector_insert: expected %d, got %d\n", 2, numbers[2]);
    check(numbers[3] == 3, "\nvector_insert: expected %d, got %d\n", 3, numbers[3]);
}

void test_vector_remove() {
    dsa_vector_t* v = vector_create(sizeof(int), 10, NULL);
    int a = 1, b = 2, c = 3;
    vector_push_back(v, &a, NULL);
    vector_push_back(v, &b, NULL);
    vector_push_back(v, &c, NULL); // [1, 2, 3]

    int x = 0;
    vector_remove(v, &x, 1, NULL); // [1, 3]

    int* numbers = vector_data(v);
    check(numbers[0] == 1, "\nvector_remove: expected %d, got %d\n", 1, numbers[0]);
    check(numbers[1] == 3, "\nvector_remove: expected %d, got %d\n", 3, numbers[1]);
}

int main(void) {
    test_vector_create();
    test_vector_push_back();
    test_vector_pop_back();
    test_vector_insert();
    test_vector_remove();

    summary();
    return g_failed > 0;
}
