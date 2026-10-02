#include "dsa.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>

static int g_tests = 0;
static int g_failed = 0;

static void check(bool eq, const char* fmt, ...) {
    g_tests++;
    if (!eq) {
        g_failed++;
        va_list args;
        va_start(args, fmt);
        vfprintf(stderr, fmt, args);
        va_end(args);
    }
}

void test_vector_create() {
    dsa_vector_t* v = vector_create(sizeof(int), 10, NULL);
    check(v != NULL, "\nvector_create: valid arguments return NULL.\n");
    vector_destroy(v);
}

int main(void) {
    test_vector_create();
    return g_failed > 0;
}
