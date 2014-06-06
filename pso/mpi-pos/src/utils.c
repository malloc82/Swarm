#include "pso.h"

double inner(double * x, double * y, const int n)
{
    double sum = 0;
    int i;
    for (i = 0; i < n; ++i) {
        sum += (x[i]*y[i]);
    }
    return sum;
}

