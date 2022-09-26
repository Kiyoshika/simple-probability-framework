#ifndef DERIVATIVES_H
#define DERIVATIVES_H

#include <stddef.h>

// forward declaration
struct param_t;
struct expression_t;
struct distribution_t;

float spf_derive_log_pdf(
    float x,
    struct distribution_t* dist,
    const size_t param_index);

float spf_derive_expression(
    struct expression_t* expression,
    const void* data,
    const size_t param_index);

#endif