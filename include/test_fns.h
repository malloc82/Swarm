#ifndef _TEST_FNS_H_
#define _TEST_FNS_H_

#include <stdlib.h>
#include <math.h>

typedef double (*func_type)(const double *, const size_t);

extern double ackley_a;
extern double ackley_b;
extern double ackley_c;

double ackley(const double *, const size_t);

extern double michalewicz_m;

double michalewicz(const double *, const size_t);

double rastrigin(const double *, const size_t);

#endif /* _TEST_FNS_H_ */
