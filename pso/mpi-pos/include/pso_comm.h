#ifndef PSO_COMM_H
#define PSO_COMM_H

#include "pso_mpi.h"
#include "pso.h"

int * setup_neighbors(const int, const int, size_t *);

void pso_mpi_init(PSO_parameters *);

double * neighbors_recv_update(const int *, const size_t, const size_t *, size_t *);

void neighbors_send_update(const PSO_status *, const int *, const size_t);

#endif /* PSO_COMM_H */
