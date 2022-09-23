# SPF - Simple Probability Framework
This is an experimental library to build independent or dependent probability models. Note that this project may not see completion


**NOTICE**: All items listed below are conceptual ideas and the general roadmap. None of these are really implemented yet.
=====

Fit a probabilistic model to data and estimate its parameters using maximum likelihood. You can then sample from this distribution, integrate it, or generate sampling distributions for its parameters.

You can also let parameters themselves follow a distribution to create compound distributions. You can use these to estimate statistics on marginal distributions such as mean, variance, etc. E.g.,

```text
X ~ Poisson(5)
Y ~ Poisson(X)

P(Y) = integral P(Y|X)P(X)dX
```

You can also define a parameter as an expression of other parameters. For example, to define a linear regression model (in terms of probability):

```text
B0 = constant parameter
B1 = constant parameter
x = data
mu = B0 + B1 * x
sigma = constant parameter

Y ~ N(mu, sigma)
```

Then you can estimate B0 and B1 with maximium likelihood and optionally generate their respective sampling distributions to get their standard errors.