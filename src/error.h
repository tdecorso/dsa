#ifndef H_DSA_ERROR
#define H_DSA_ERROR

#include "dsa.h"

#ifndef DSA_ERROR_MAX_LEN
#define DSA_ERROR_MAX_LEN 128
#endif

struct error {
    dsa_error_type_t type;
    char msg[DSA_ERROR_MAX_LEN];
};

void format_error(dsa_error_t* err, dsa_error_type_t type, const char* fmt, ...);

#endif
