#ifndef IO_H
#define IO_H

#include "pso.h"

void read_parameter_size_t(char * , size_t * , const char *);

void read_parameter_double(char *, double *, const char *);

void read_parameter_range(char *, PSO_parameters *);

void read_parameter_data_double(char *,  double **, const size_t);

func_type read_parameter_func_type(char *, const char *);

void print_parameters(const PSO_parameters *);

void print_double_vec(const char *, const double *, const size_t, const char *);

void pso_print_result(const size_t, const double *, const size_t, const double);

#endif /* IO_H */
