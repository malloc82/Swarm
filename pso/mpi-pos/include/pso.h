#ifndef PSO_H
#define PSO_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265359
#define E  2.7182818284

extern double ackley_a;
extern double ackley_b;
extern double ackley_c;

double ackley(double *, const int);
double michalewicz(double *, const int);
double rastrigin(double *, const int);

double inner(double *, double *, const int);

#endif // PSO
