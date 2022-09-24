#include "expression.h"
#include "spferr.h"
#include "param.h"

struct expression_t* spf_expression_create(
    struct param_t** parameters,
    size_t n_parameters,
    float (*evaluate)(struct param_t**, const void*))
{
    struct expression_t* expression = malloc(sizeof(struct expression_t));
    if (!expression)
        spf_err("spf_create_expression: Couldn't allocate memory for new expression.");
    
    expression->parameters = parameters;
    expression->n_parameters = n_parameters;
    expression->evaluate = evaluate;

    return expression;
}

void spf_expression_free(
    struct expression_t** expression)
{
    for (size_t i = 0; i < (*expression)->n_parameters; ++i)
        spf_param_free(&(*expression)->parameters[i]);
    
    free((*expression)->parameters);
    (*expression)->parameters = NULL;
    
    free(*expression);
    *expression = NULL;
}