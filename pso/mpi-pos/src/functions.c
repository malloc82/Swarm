#include "utils.h"
#include "test_fns.h"

double ackley_a = 20;
double ackley_b = 0.2;
double ackley_c = 2*PI;

double ackley(const double * x, const size_t n)
{
    /* printf("\n a = %f, b = %f, c = %f\n", ackley_a, ackley_b, ackley_c); */
    size_t i;
    double temp_val_1 = sqrt(inner(x, x, n)/n);
    double temp_sum = 0;
    for (i = 0; i < n; ++i) {
        temp_sum += cos(ackley_c*x[i]);
    }
    temp_sum = temp_sum/n;
    return (-ackley_a)*exp((-ackley_b)*temp_val_1) - exp(temp_sum) + ackley_a + exp(1);
}

double michalewicz_m = 10;

double michalewicz(const double * x, const size_t n)
{
    double y = 0;
    size_t i;
    for (i = 0; i < n; ++i) {
        const double xi = x[i];
        y = y - sin(xi) * pow(sin(((i + 1)*xi*xi)/PI), 2*michalewicz_m);
    }
    return y;
}

double rastrigin(const double * x, const size_t n)
{
    double y = 10 * n;
    size_t i;
    for (i = 0; i < n; ++i) {
        const double xi = x[i];
        y += xi*xi - 10*cos(2*PI*xi);
    }
    return y;
}
