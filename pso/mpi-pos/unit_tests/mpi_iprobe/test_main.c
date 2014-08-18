#include <mpi.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define RECVER 0
#define SENDER 1

#define CHANN  0

void sender_fn(const int id, const int p)
{
    char * data_text = "sender test";
    size_t length = strlen(data_text) + 1;
    MPI_Send((void *)data_text, length, MPI_CHAR, RECVER, CHANN, MPI_COMM_WORLD);
    printf("\n (%d) : data sent", id);
    fflush(stdout);
    return;
}

void recver_fn(const int id, const int p)
{
    char data_buffer[16];
    int flag = 0;
    MPI_Status status;
    printf("\n (%d) : receiver going to sleep ... ", id);
    fflush(stdout);

    sleep(5);

    printf("\n (%d) : receiver wake up", id);
    printf("\n (%d) : probe return %d", id, MPI_Iprobe(SENDER, CHANN, MPI_COMM_WORLD, &flag, &status));
    fflush(stdout);

    if (flag) {
        MPI_Recv((void *)data_buffer, 16, MPI_CHAR, SENDER, CHANN, MPI_COMM_WORLD, &status);
        printf("\n (%d) : Data received: %s", id, data_buffer);
        fflush(stdout);
    } else {
        printf("\n (%d) : No data to receive", id);
        fflush(stdout);
    }
    return;
}

void switch_board(const int id, const int p)
{
    switch(id) {
        case RECVER:
            recver_fn(id, p);
            break;
        case SENDER:
            sender_fn(id, p);
            break;
        default:
            break;
    }
    return;
}

int main(int argc, char *argv[])
{
    int p, id;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (id == 0) {
        printf("\n size of size_t             = %lu", sizeof(size_t));
        printf("\n size of short              = %lu", sizeof(short));
        printf("\n size of unsigned int       = %lu", sizeof(unsigned int));
        printf("\n size of unsigned long      = %lu", sizeof(unsigned long));
        printf("\n size of unsigned long long = %lu", sizeof(unsigned long long));
        printf("\n size of MPI_UINT64_T       = %lu", sizeof(MPI_UINT64_T));
        puts("");
    }

    fflush(stdout);


    switch_board(id, p);

    MPI_Finalize();
    puts("");
    return 0;
}
