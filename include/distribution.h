#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include <stddef.h>
#include <stdlib.h>

#include "param.h"

enum distribution_type_e
{
    DISCRETE,
    CONTINUOUS
};

struct distribution_t
{
    // type of distribution (DISCRETE or CONTINUOUS)
    enum distribution_type_e type;

    // parameters of the distribution
    struct param_t* parameters;
    const size_t n_parameters;

    // probability density
    float (*density)(const float x, const struct param_t* parameters);
};

struct distribution_t* spf_dist_create(
    enum distribution_type_e type,
    const size_t n_parameters);

void spf_dist_set_param(
    struct distribution_t** dist,
    struct param_t* param,
    const size_t param_index);

void spf_dist_set_density(
    struct distribution_t** dist,
    float (*density)(const float, const struct param_t*));

#endif