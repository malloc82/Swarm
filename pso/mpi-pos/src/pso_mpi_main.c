#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int id = -1;
    int p  = 0;
    int c; 
    unsigned int dimension = 0, agents_count = 0;
    char * endptr;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    
    while ((c = getopt(argc, argv, "d:n:")) != -1) { 
        switch (c) {
            case 'd':
                errno = 0; 
                dimension = strtol(optarg, &endptr, 10);
                if ((errno == ERANGE && (dimension == LONG_MAX || dimension == LONG_MIN)) 
                    || (errno != 0 && dimension = 0)) {
                    perror("strtol");
                    MPI_Finalize();
                    exit(EXIT_FAILURE);
                }
                if (endptr == optarg) {
                    fprintf(stderr, "No digits were found\n");
                    MPI_Finalize();
                    exit(EXIT_FAILURE);
                }
                break;
            case 'n':
                errno = 0; 
                agents_count = strtol(optarg, &endptr, 10);
                if ((errno == ERANGE && (agents_count == LONG_MAX || agents_count == LONG_MIN)) 
                    || (errno != 0 && agents_count = 0)) {
                    perror("strtol");
                    MPI_Finalize();
                    exit(EXIT_FAILURE);
                }
                if (endptr == optarg) {
                    fprintf(stderr, "No digits were found\n");
                    MPI_Finalize();
                    exit(EXIT_FAILURE);
                }
                break;
            default:
                puts("Unrecognized flag ... abort");
                MPI_Finalize();
                exit(EXIT_FAILURE);
        }
    }
    if (dimension == 0 || agents_count == 0) {
        puts("Missing either dimension or agents_count, cannot proceed.");
        MPI_Finalize();
        exit(EXIT_FAILURE);
    }

    unsigned int local_agents_count = (unsigned int)ceil(agents_count / (double)p);
    
    return 0;
}
