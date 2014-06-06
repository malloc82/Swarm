#ifndef PSO_H
#define PSO_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define PI 3.14159265359
#define E  2.7182818284

extern double ackley_a;
extern double ackley_b;
extern double ackley_c;

/* Test functions */ 
double ackley(double *, const int);
double michalewicz(double *, const int);
double rastrigin(double *, const int);

/* Inner product of two vectors */
double inner(double *, double *, const int);

/* Generate a random double between two numbers */
double randrange(const double, const double);

/* Generate a random vector (double) of given size based on given range for each dimension */
int    randrange_array(const double *, const double *, double **, const size_t);


#endif // PSO
