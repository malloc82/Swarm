#include "test_fns.h"

double funcall_test(double (*fn)(const double *, const int),
                    PSO_parameters * parameters)
{
    const int dim = 5;
    double * a = alloca(dim*sizeof(double));
    a[0] = -1;
    a[1] = -2;
    a[2] = -3;
    a[3] =  2;
    a[4] =  1;
    return fn(a, dim);
}
