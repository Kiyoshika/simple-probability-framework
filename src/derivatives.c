#include "derivatives.h"
#include "param.h"
#include "expression.h"
#include "distribution.h"

float spf_derive_log_pdf(
    float x,
    struct distribution_t* dist,
    const size_t param_index)
{
    // TODO: make copy distributions and adjust parameter with offsets to take
    // derivative of density with respect to certain parameter.
    // currently this takes derivative with respect to x which doesn't really do much
    float offset = 0.0001f;
    return (dist->log_density(x + offset, dist) - dist->log_density(x - offset, dist)) / (2*offset);
}

float spf_derive_expression(
    struct expression_t* expression,
    const void* data,
    const size_t param_index)
{
    // create copy of (modified) scalar parameters in order to compute partial derivatives
    struct param_t** param_copy_under = malloc(sizeof(struct param_t*) * expression->n_parameters);
    struct param_t** param_copy_over = malloc(sizeof(struct param_t*) * expression->n_parameters);

    float offset = 0.0f;
    for (size_t p = 0; p < expression->n_parameters; ++p)
    {
        offset = 0.0f;
        if (p == param_index)
            offset = 0.001f;

        param_copy_under[p] = spf_param_create_scalar(expression->parameters[p]->scalar - offset);
        param_copy_over[p] = spf_param_create_scalar(expression->parameters[p]->scalar + offset);
    }

    float derivative = (expression->evaluate(param_copy_over, data) - expression->evaluate(param_copy_under, data)) / (2*0.001f);

    for (size_t p = 0; p < expression->n_parameters; ++p)
    {
        spf_param_free(&param_copy_over[p]);
        spf_param_free(&param_copy_under[p]);
    }
    free(param_copy_over);
    free(param_copy_under);

    return derivative;
}