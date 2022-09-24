#ifndef PARAM_H
#define PARAM_H

#include <stddef.h>
#include <stdlib.h>

enum param_type_e
{
    SCALAR,
    EXPRESSION,
    DISTRIBUTION
};

// forward declarations
struct distribution_t;
struct expression_t;

struct param_t
{
    enum param_type_e type;

    // parameter can be a scalar value, expression (combination of other parameters) or distribution
    union
    {
        float scalar;
        struct expression_t* expression;
        struct distribution_t* distribution;
    };
};

struct param_t* spf_param_create(
    enum param_type_e type);

void spf_param_set_value(
    struct param_t** param, float value);

void spf_param_set_expression(
    struct param_t** param,
    struct expression_t* expression);

float spf_param_evaluate(
    const struct param_t* param,
    const void* data);

void spf_param_free(
    struct param_t** param);

#endif