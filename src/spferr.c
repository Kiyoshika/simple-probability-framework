#include "spferr.h"

void spf_err(const char* msg)
{
    fprintf(stderr, "%s\n", msg);
    abort();
}