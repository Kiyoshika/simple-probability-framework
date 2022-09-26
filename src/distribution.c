#include "distribution.h"
#include "spferr.h"

struct distribution_t* spf_dist_create(
    enum distribution_type_e type,
    size_t n_parameters)
{
    struct distribution_t* dist = malloc(sizeof(struct distribution_t));
    if (!dist)
        spf_err("spf_dist_create: Couldn't allocate memory for new distribution.");
    
    dist->type = type;
    dist->n_parameters = n_parameters;

    dist->parameters = malloc(sizeof(struct param_t*) * n_parameters);
    if (!dist->parameters)
        spf_err("spf_dist_create: Couldn't allocate memory for new distribution.");
    
    for (size_t p = 0; p < n_parameters; ++p)
        dist->parameters[p] = NULL;

    dist->density = NULL;

    dist->data = NULL;

    return dist;
}

void spf_dist_set_param(
    struct distribution_t** dist,
    struct param_t* param,
    const size_t param_index)
{
    (*dist)->parameters[param_index] = param;
}

float spf_dist_evaluate(
    struct distribution_t* dist,
    float x)
{
    return dist->density(x, dist);
}

void spf_dist_set_density(
    struct distribution_t** dist,
    float (*density)(float, struct distribution_t*),
    float (*log_density)(float, struct distribution_t*))
{
    (*dist)->density = density;
    (*dist)->log_density = log_density;
}

void spf_dist_free(
    struct distribution_t** dist)
{
    for (size_t p = 0; p < (*dist)->n_parameters; ++p)
        spf_param_free(&(*dist)->parameters[p]);
    
    free((*dist)->parameters);
    (*dist)->parameters = NULL;
    
    free(*dist);
    *dist = NULL;
}