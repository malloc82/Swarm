#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int id = -1;
    int p  = 0;
    int c; 
    int dimension = 0;
    char * endptr;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    
    while ((c = getopt(argc, argv, "d:")) != -1) { 
        switch (c) {
            case 'd':
                errno = 0; 
                dimension = strtol(optarg, &endptr, 10);
                if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) || (errno != 0 && val = 0)) {
                    perror("strtol");
                    exit(EXIT_FAILURE);
                }
                if (endptr == optarg) {
                    fprintf(stderr, "No digits were found\n");
                    exit(EXIT_FAILURE);
                }
                break;
            default:
                puts("Unrecognized flag ... abort");
                abort();
        }
    }
    return 0;
}
