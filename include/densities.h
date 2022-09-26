#ifndef DENSITIES_H
#define DENSITIES_H

#include <math.h>
#include <stddef.h>

// forward declaration
struct distribution_t;

// Bernoulli distribution to model binary 0 and 1 outcomes with
// a single parameter, theta (dist->parameters[0]).
// P(x; theta) = theta^x * (1-theta)^(1-x)
float spf_density_bernoulli(
    float x, 
    struct distribution_t* dist);

// logarithm of spf_density_bernoulli.
// used in optimization algorithm when computing MLE estimates.
float spf_log_density_bernoulli(
    float x,
    struct distribution_t* dist);

#endif