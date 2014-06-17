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
#include <string.h>

#define PI 3.14159265359
#define E  2.7182818284

extern double ackley_a;
extern double ackley_b;
extern double ackley_c;

/* Test functions */
double ackley      (const double *, const int);
double michalewicz (const double *, const int);
double rastrigin   (const double *, const int);

/* Inner product of two vectors */
double inner(const double *, const double *, const int);

/* Generate a random double between two numbers */
double randrange(const double, const double);

/* Generate a random vector (double) of given size based on given range for each dimension */
double * rand_array_varying_range(const double *, const double *, const size_t);
double * rand_array_fixed_range(const double, const double, const size_t);

/* PSO types */
typedef struct {
    unsigned int dimension;
    unsigned int agents_count;
    double       precision;
} PSO_parameters;

typedef struct {
    double lo;
    double hi;
} PSO_range;

typedef struct {
    size_t   dim;
    double * lo;
    double * hi;
} PSO_dim_range;

typedef struct {
    double * pos;
    double   val;
} PSO_state; /* Try to use heap for this one */

/* Search functions */
PSO_state * pso_search(double (*)(const double *, const int),
                       const PSO_range *,
                       const PSO_parameters *);

/* PSO utility functions */
double ** new_agents_pos(const size_t, const size_t);
double ** release_agents_pos(double **, const size_t);
PSO_state * new_agents_states(const size_t,
                              const size_t,
                              const PSO_range *,
                              double (*)(const double *, const int));
PSO_state * reset_state(PSO_state *);
PSO_state * release_agents_states(PSO_state *, const size_t);

#endif // PSO
