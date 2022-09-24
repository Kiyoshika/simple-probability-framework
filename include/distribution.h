#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "param.h"

enum distribution_type_e
{
    DISCRETE,
    CONTINUOUS
};

struct distribution_t
{
    // will create a custom type for this later.
    // for now this will be void*
    void* data;

    // type of distribution (DISCRETE or CONTINUOUS)
    enum distribution_type_e type;

    // parameters of the distribution
    struct param_t** parameters;
    size_t n_parameters;

    // probability density
    float (*density)(const float x, struct param_t** parameters, const void* data);
};

// create new distribution with N (empty) parameters.
struct distribution_t* spf_dist_create(
    enum distribution_type_e type,
    const size_t n_parameters);

// set the i-th parameter in the distribution.
// note that ownership of the param pointer is transferred to the distribution
// so it will be free'd with the distribution as well.
void spf_dist_set_param(
    struct distribution_t** dist,
    struct param_t* param,
    const size_t param_index);

void spf_dist_set_density(
    struct distribution_t** dist,
    float (*density)(const float, struct param_t**, const void*));

// evaluate probability density/mass
float spf_dist_evaluate(
    const struct distribution_t* dist,
    const float x);

void spf_dist_free(
    struct distribution_t** dist);

#endif