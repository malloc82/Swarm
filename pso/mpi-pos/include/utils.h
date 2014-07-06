#ifndef UTILS_H
#define UTILS_H

#include "pso.h"

double inner(const double *, const double * y, const size_t);

double norm1(const double *, const size_t);

double norm2(const double *, const size_t);

void normalize(double, const size_t);

double sd(const double * x, const size_t);

double randrange(const double, const double);

double * rand_array_varying_range(const PSO_range *, const size_t);

double * rand_array_fixed_range(const double, const double, const size_t);

#endif /* UTILS_H */
