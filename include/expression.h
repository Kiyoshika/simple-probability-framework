#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <stddef.h>
#include <stdlib.h>

// forward declaration
struct param_t;

struct expression_t
{
    struct param_t** parameters;
    size_t n_parameters;
    float (*evaluate)(struct param_t** parameters, const void* data);
};

struct expression_t* spf_expression_create(
    struct param_t** parameters,
    size_t n_parameters,
    float (*evaluate)(struct param_t**, const void*));

// numerically compute the partial derivative on the i-th parameter in the expression
float spf_expression_gradient(
    const struct expression_t* expression,
    const size_t parameter_index);

void spf_expression_free(
    struct expression_t** parameters);

#endif