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