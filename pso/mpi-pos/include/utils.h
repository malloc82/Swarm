#ifndef UTILS_H
#define UTILS_H

#include <sys/types.h>

#define PI 3.14159265359
#define E  2.7182818284

typedef struct {
    double lo;
    double hi;
} Range;

double inner(const double *, const double * y, const size_t);

double norm1(const double *, const size_t);

double norm2(const double *, const size_t);

double mean(const double *, const size_t);

void normalize(double *, const size_t);

double sd(const double * x, const size_t);

double randrange(const double, const double);

double * rand_array_varying_range(const Range *, const size_t);

double * rand_array_fixed_range(const double, const double, const size_t);

#endif /* UTILS_H */
