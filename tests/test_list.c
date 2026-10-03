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

void test_list_create() {
    dsa_list_t* l = list_create(sizeof(int), NULL);
    check(l != NULL, "\nlist_create: valid arguments return NULL.\n");
    list_destroy(l);
}

int main(void) {
    test_list_create();
    summary();
    return g_failed > 0;
}
