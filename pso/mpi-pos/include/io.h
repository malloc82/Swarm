#ifndef IO_H
#define IO_H

#include "pso.h"

size_t read_parameter_size_t(char *, const char *);

double read_parameter_double(char *, const char *);

func_type read_parameter_func_type(char *, const char *);

void read_parameter_range(char *, PSO_parameters *);

void read_parameter_data_double(char *,  double **, const size_t);

void print_parameters(const PSO_parameters *);

void print_double_vec(const char *, const double *, const size_t);

void pso_print_result(const size_t, const double *, const size_t, const double);

#endif /* IO_H */
