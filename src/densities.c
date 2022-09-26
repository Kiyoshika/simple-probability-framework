#include "densities.h"
#include "param.h"
#include "expression.h"
#include "distribution.h"

float spf_density_bernoulli(
    float x,
    struct distribution_t* dist)
{
    float theta = 0.0f;
    
    if (dist->parameters[0]->type == SCALAR)
        theta = dist->parameters[0]->scalar;
    if (dist->parameters[0]->type == EXPRESSION)
        theta = dist->parameters[0]->expression->evaluate(dist->parameters[0]->expression->parameters, dist->data);

    return powf(theta, x) * powf((1.0f - theta), (1.0f - x));
}

float spf_log_density_bernoulli(
    float x,
    struct distribution_t* dist)
{
    return logf(spf_density_bernoulli(x, dist));
}