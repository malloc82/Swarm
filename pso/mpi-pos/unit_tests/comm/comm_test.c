#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#include "utils.h"
#include "pso_comm.h"

typedef struct {
    int sender;
    int count;
    int receivers[4];
} Test_obj;

#define DIM 4

void print_test_data(const char * msg, const int id, const double * data, const size_t dim)
{
    if (data == NULL || dim == 0) {
        printf("\n (%02d) data = (NULL)", id);
    } else {
        printf("\n %20s (%02d) = [%6.3f", msg, id, data[0]);
        size_t i;
        for (i = 1; i < dim; ++i) {
            printf(", %6.3f", data[i]);
        }
        printf("];  val = %6.3f", data[dim]);
    }
    fflush(stdout);
    return;
}

void print_test_status(const char * msg, const int id, const PSO_status * status)
{
    if (status == NULL) {
        printf("\n (%02d) data = (NULL)", id);
    } if(status && status->pos_best) {
        printf("\n"
               "\n    ---------------------------------------------------------------------------");
        printf("\n %20s (%02d) = [%6.3f", msg, id, status->pos_best[0]);
        size_t i;
        for (i = 1; i < status->dimension; ++i) {
            printf(", %6.3f", status->pos_best[i]);
        }
        printf("];  val = %6.3f", status->val_best);
        printf("\n    --------------------------------------------------------------------------- \n");
    }
    fflush(stdout);
    return;
}

void sender_test_fn(const int id, const int p, const Test_obj * obj)
{
    PSO_status status;
    status.dimension   = DIM;
    status.pos_best    = rand_array_fixed_range(0, 1, status.dimension);
    status.val_best    = randrange(0, 1);
    print_test_status("data to be sent", 0, &status);
    printf("\n Start sending data ...");
    neighbors_send_update(&status, obj->receivers, obj->count);
    printf("\n Sender complete");
    fflush(stdout);
    free(status.pos_best);
    return;
}

void receiver_test_fn(const int id, const int p, const Test_obj * obj)
{
    int neighbor[] = {obj->sender};
    size_t best_index;
    double * data = neighbors_recv_update(neighbor, 1, DIM, &best_index);
    if (data) {
        print_test_data("data received", id, data, DIM);
        free(data);
    }
}

int scheduler(const int id, const int p, const Test_obj * obj)
{
    if (id == obj->sender) {
        sender_test_fn(id, p, obj);
        sleep(1);
        sender_test_fn(id, p, obj);
        sleep(1);
        sender_test_fn(id, p, obj);

    } else if (id == obj->receivers[0] ||
               id == obj->receivers[1] ||
               id == obj->receivers[2] ||
               id == obj->receivers[3]) {
        clock_t timeout = 7 * CLOCKS_PER_SEC;
        clock_t curr_clock = clock();
        while (clock() - curr_clock < timeout) {
            receiver_test_fn(id, p, obj);
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int id, p;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    Test_obj obj = {0,
                    4,
                    {1, 2, 3, 4}};

    printf("\n %d Comm Test", id);
    fflush(stdout);
    scheduler(id, p, &obj);
    MPI_Finalize();
    puts("");
    return 0;
}
