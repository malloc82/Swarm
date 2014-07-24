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
#include "test_fns.h"

#define PI 3.14159265359
#define E  2.7182818284

/* PSO types */
typedef struct {
    double lo;
    double hi;
} Range;

typedef struct {
#ifdef PSO_MPI
    int     id;                 /* Used for MPI */
    int     p;
    int   * neighbors;
    size_t  neighbors_count;
#endif
    size_t  dimension;
    Range * ranges;
    size_t  agents_count;
    double  precision;
    size_t  max_runs;
    double  w;
    double  a1;
    double  a2;
} PSO_parameters;

typedef struct {
    double * pos;
    double * v;
    double * pos_best;
    double   val_best;
} PSO_state;

typedef struct {
    size_t      dimension;
    size_t      agents_count;
    PSO_state * agents_states;
    double    * sd_pos;
    double      v_max;
    int         index_best;
    double    * pos_best;
    double      val_best;
} PSO_status;

/* search */
PSO_status pso_init(func_type, const PSO_parameters *);

void update_status(PSO_status *);

void pso_iteration(func_type, const PSO_parameters *, PSO_status *);

PSO_status pso_search(func_type, const PSO_parameters *);

/* agents */
double v_max_dim(const double);

double new_v_max(const double *, const size_t, const double);

double sd_dim(const PSO_state *, const size_t, const size_t);

void update_sd_pos(double *, const PSO_state *, const size_t, const size_t);

PSO_state * init_agents(func_type, const PSO_parameters *);

PSO_state * free_agents(PSO_state * agents, const PSO_parameters *);

void clear_status(PSO_status *, const PSO_parameters *);

void clear_parameters(PSO_parameters *);

#endif // PSO
