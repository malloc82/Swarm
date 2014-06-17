#include "pso.h"

double ackley_a = 20;
double ackley_b = 0.2;
double ackley_c = 2*PI;

double ackley(const double * x, const int n)
{
    /* printf("\n a = %f, b = %f, c = %f\n", ackley_a, ackley_b, ackley_c); */
    int i;
    double temp_val_1 = sqrt(inner(x, x, n)/n);
    double temp_sum = 0;
    for (i = 0; i < n; ++i) {
        temp_sum += cos(ackley_c*x[i]);
    }
    temp_sum = temp_sum/n;
    return (-ackley_a)*exp((-ackley_b)*temp_val_1) - exp(temp_sum) + ackley_a + exp(1);
}

