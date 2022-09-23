#ifndef PARAM_H
#define PARAM_H

enum param_type_e
{
    CONSTANT,
    EXPRESSION,
    DISTRIBUTION
};

// forward declaration
struct distribution_t;

struct param_t
{
    enum param_type_e type;

    // parameter can be a constant value, expression (combination of other parameters) or distribution
    union value_t
    {
        float constant;
        float (*expression)(struct param_t* parameters, void* data);
        struct distribution_t* distribution;
    };
};

struct param_t* spf_param_create(
    enum param_type_e type);

void spf_param_set_value(
    struct param_t** param, float value);

void spf_param_set_expression(
    struct param_t** param, 
    float (*expression)(struct param_t* parameters, void* data));

#endif