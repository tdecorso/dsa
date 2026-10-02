#ifndef H_DSA_ERROR
#define H_DSA_ERROR

#include "dsa.h"

void format_error(dsa_error_t* err, dsa_error_type_t type, const char* fmt, ...);

#endif
