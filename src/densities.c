#include "densities.h"
#include "param.h"

float spf_density_bernoulli(
    const float x,
    struct param_t** params,
    const void* data)
{
    float theta = spf_param_evaluate(params[0], data);
    return powf(theta, x) * powf((1.0f - theta), (1.0f - x));
}