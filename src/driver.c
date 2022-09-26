#include "spf.h"
#include "derivatives.h" // technically this is an internal header, but including for demenstration

#include <stdio.h>

float evaluate(struct param_t** params, const void* data)
{
    // theta1 + 3*theta2
    return spf_param_evaluate(params[0], NULL) + 3.0f * spf_param_evaluate(params[1], NULL);
}

int main()
{
    struct param_t* theta1 = spf_param_create_scalar(0.25f);
    struct param_t* theta2 = spf_param_create_scalar(0.15f);

    struct param_t** param_list = spf_param_create_list(
        2,
        theta1,
        theta2);

    struct expression_t* theta_exp = spf_expression_create(param_list, 2, &evaluate);

    struct param_t* theta = spf_param_create(EXPRESSION);
    spf_param_set_expression(&theta, theta_exp);

    struct distribution_t* bernoulli = spf_dist_create(DISCRETE, 1);
    spf_dist_set_param(&bernoulli, theta, 0);
    spf_dist_set_density(&bernoulli, &spf_density_bernoulli, &spf_log_density_bernoulli);

    printf("Param Value: %f\n", spf_param_evaluate(theta, NULL));
    printf("Proba: %f\n", spf_dist_evaluate(bernoulli, 0.0f));

    // compute numerical derivatives
    float exp_derivative = spf_derive_expression(theta_exp, NULL, 1);
    printf("Derivative w.r.t theta2: %f\n", exp_derivative);

    float pdf_derivative = spf_derive_log_pdf(0.5f, bernoulli);
    printf("Derivative of log bernoulli at 0: %f\n", pdf_derivative);

    // note: anything added to a distribution transfers ownership.
    // thus, it's only necessary to free the distribution as it will take care
    // of all its dependencies
    spf_dist_free(&bernoulli);

    return 0;
}