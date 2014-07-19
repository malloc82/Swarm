#include "pso_comm.h"

int * setup_neighbors(const int id, const int p, size_t * count)
{
    if (id >= 0 && p > 0) {
        int * neighbors = malloc(sizeof(int) * 4);

        const int width   = ceil(sqrt(p));
        const int last_id = p - 1;
        const int row     = id / width;
        const int col     = id % width;
        const int max_row = last_id / width;
        const int max_col = last_id % width;

        /* printf("\n width = %d", width); */
        /* printf("\n row = %d, col = %d", row, col); */
        /* printf("\n max_row = %d, max_col = %d", max_row, max_col); */

        *count = 0;
        /* up */
        if (row == 0) {
            if (col <= max_col) {
                neighbors[*count] = max_row * width + col;
            } else {
                neighbors[*count] = (max_row - 1) * width + col;
            }
        } else {
            neighbors[*count] = (row - 1) * width + col;
        }
        (*count) += (neighbors[*count] == id) ? 0 : 1; /* update count */

        /* down */
        if (row == max_row || col > max_col) {
            neighbors[*count] = col;
        } else {
            neighbors[*count] = (row + 1) * width + col;
        }
        (*count) += (neighbors[*count] == id ||
                     (*count != 0 && neighbors[(*count)-1] == neighbors[*count])) ? 0 : 1;

        /* left */
        if (col == 0) {
            neighbors[*count] = (row < max_row) ? (row + 1) * width - 1 : last_id;
        } else {
            neighbors[*count] = row * width + (col - 1);
        }
        (*count) += (neighbors[*count] == id ||
                     (*count != 0 && neighbors[(*count)-1] == neighbors[*count])) ? 0 : 1;

        /* right */
        if ((col == width - 1) || (row == max_row && id == last_id)) {
            neighbors[*count] = row * width;
        } else {
            neighbors[*count] = row * width + col + 1;
        }
        (*count) += (neighbors[*count] == id ||
                     (*count != 0 && neighbors[(*count)-1] == neighbors[*count])) ? 0 : 1;

        size_t i;
        for (i = *count; i < 4; ++i) {
            neighbors[i] = -1;
        }
        /* printf("\n neighbors: %d", neighbors[0]); */
        /* size_t i; */
        /* for (i = 1; i < 4; ++i) { */
        /*     if (neighbors[i] >=0 ) */
        /*         printf(", %d", neighbors[i]); */
        /* } */
        /* puts("\n"); */
        return neighbors;
    } else {
        printf("\n Failure: Id needs to be non-negative, p needs to be positive \n");
        return NULL;
    }
}

void pso_mpi_init(PSO_parameters * parameters)
{
    parameters->neighbors = setup_neighbors(parameters->id,
                                            parameters->p,
                                            &parameters->neighbors_count);
    return;
}

double * neighbors_recv_update(const int    * neighbors,
                               const size_t   count,
                               const size_t * dim,
                               size_t       * neighbors_best)
{
    const size_t pos_size   = sizeof(double) * dim;
    const size_t data_size  = sizeof(double) * (dim + 1);
    const size_t data_count = dim + 1;

    double * data = alloca(data_size);
    double * neighbors_data = NULL;

    MPI_Status status;
    size_t i;
    int flag = 0;
    for (i = 0; i < count; ++i) {
        MPI_Iprobe(neighbors[i], 0, MPI_COMM_WORLD, &flag, &status);
        if (flag) {
            MPI_Recv(&data, data_count, MPI_DOUBLE, neighbors[i], 0, MPI_COMM_WORLD, &status);
            if (neighbors_data) {
                if (data[dim] < neighbors_data[dim]) {
                    memcpy(neighbors_data, data, data_size);
                    *neighbors_best = i;
                }
            } else {
                neighbors_data = malloc(data_size);
                memcpy(neighbors_data, data, data_size);
                *neighbors_best = i;
            }
        }
    }
    if (!neighbors_data) {
        return data;
    } else {
        free(data);
        return NULL;
    }
}

void neighbors_send_update(const PSO_status * swarm_status,
                           const int        * neighbors,
                           const size_t       count)
{
    const size_t dim = swarm_status->dimension;
    double * data    = alloca(sizeof(double) * (dim + 1));
    memcpy(data, swarm_status->pos_best, sizeof(double) * dim);
    data[dim] = swarm_status->val_best;
    size_t i;
    for (i = 0; i < count; ++i) {
        MPI_Send((void *)data, dim + 1, MPI_DOUBLE, neighbors[i], 0, MPI_COMM_WORLD);
    }
    return;
}
