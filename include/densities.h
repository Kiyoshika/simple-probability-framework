#ifndef DENSITIES_H
#define DENSITIES_H

#include <math.h>
#include <stddef.h>

// forward declaration
struct param_t;

// Bernoulli distribution to model binary 0 and 1 outcomes with
// a single parameter, theta (params[0]).
// P(x; theta) = theta^x * (1-theta)^(1-x)
float spf_density_bernoulli(
    const float x, 
    struct param_t** params,
    const void* data);

#endif