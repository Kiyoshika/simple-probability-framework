#include "param.h"
#include "distribution.h"
#include "spferr.h"
#include "expression.h"

struct param_t* spf_param_create(
    enum param_type_e type)
{
    struct param_t* param = malloc(sizeof(struct param_t));
    if (!param)
        spf_err("spf_param_create: Couldn't allocate memory for new parameter.");
    
    param->type = type;

    return param;
}

struct param_t* spf_param_create_scalar(
    float value)
{
    struct param_t* param = spf_param_create(SCALAR);
    spf_param_set_value(&param, value);

    return param;
}

struct param_t* spf_param_create_expression(
    struct expression_t* expression)
{
    struct param_t* param = spf_param_create(EXPRESSION);
    spf_param_set_expression(&param, expression);

    return param;
}

struct param_t** spf_param_create_list(
    const size_t n_parameters,
    struct param_t* param,
    ...)
{
    struct param_t** parameters = malloc(sizeof(struct param_t*) * n_parameters);
    if (!parameters)
        spf_err("spf_param_create_list: Couldn't allocate memory for parameter list.");
    
    // due to annoyingness with va_list, the dynamic args only start after
    // the first parameter is passed, so we set the first entry manually
    parameters[0] = param;

    va_list param_list;
    va_start(param_list, param);
    for (size_t p = 1; p < n_parameters; ++p)
        parameters[p] = va_arg(param_list, struct param_t*);
    va_end(param_list);

    return parameters;
}

void spf_param_set_value(
    struct param_t** param,
    float value)
{
    if ((*param)->type != SCALAR)
        spf_err("spf_set_value: Parameter must be SCALAR type to use this function.");
    
    (*param)->scalar = value;
}

void spf_param_set_expression(
    struct param_t** param,
    struct expression_t* expression)
{
    if ((*param)->type != EXPRESSION)
        spf_err("spf_set_expression: Parameter must be EXPRESSION type to use this function.");
    
    (*param)->expression = expression;
}

void spf_param_set_distribution(
    struct param_t** param,
    struct distribution_t* dist)
{
    if ((*param)->type != DISTRIBUTION)
        spf_err("spf_set_distribution: Parameter must be DISTRIBUTION type to use this function.");
    
    (*param)->distribution = dist;
}

float spf_param_evaluate(
    const struct param_t* param,
    const void* data)
{
    switch(param->type)
    {
        case SCALAR:
            return param->scalar;
        
        case EXPRESSION:
            return param->expression->evaluate(param->expression->parameters, data);
        
        case DISTRIBUTION:
            spf_err("spf_param_evaluate: DISTRIBUTION type not supported (yet) in evaluate function.");
            break;
    }

    return -1.0f;
}

void spf_param_free(
    struct param_t** param)
{
    if ((*param)->type == EXPRESSION)
        spf_expression_free(&(*param)->expression);
    
    free(*param);
    *param = NULL;
}