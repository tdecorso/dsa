#include "error.h"
#include <stdio.h>
#include <stdarg.h>

void format_error(dsa_error_t* err, dsa_error_type_t type, const char* fmt, ...) {
    if (!err) return;
    err->type = type;
    va_list args;
    va_start(args, fmt);
    vsnprintf(err->msg, DSA_ERROR_MAX_LEN, fmt, args);
    va_end(args);
}
