#include "pso.h"
#include "test_fns.h"
#include <errno.h>


int main(int argc, char *argv[])
{
    int id = -1;
    int p  = 0;
    int c;
    char * endptr;
    int words_read = 0;

    PSO_parameters parameters = {0, 0, 0.01};

    while ((c = getopt(argc, argv, "d:n:")) != -1) {
        switch (c) {
            case 'd': /* dimension */
                errno = 0;
                parameters.dimension = strtol(optarg, &endptr, 10);
                if ((errno == ERANGE &&
                     (parameters.dimension == LONG_MAX ||
                      parameters.dimension == LONG_MIN))
                    || (errno != 0 && parameters.dimension == 0)) {
                    perror("strtol: d");
                    exit(EXIT_FAILURE);
                }
                if (endptr == optarg) {
                    fprintf(stderr, "No digits were found (-d)\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'n': /* agents count */
                errno = 0;
                parameters.agents_count = strtol(optarg, &endptr, 10);
                if ((errno == ERANGE &&
                     (parameters.agents_count == LONG_MAX ||
                      parameters.agents_count == LONG_MIN))
                    || (errno != 0 && parameters.agents_count == 0)) {
                    perror("strtol: n");
                    exit(EXIT_FAILURE);
                }
                if (endptr == optarg) {
                    fprintf(stderr, "No digits were found (-n) \n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'p': /* precision */
                words_read = sscanf(optarg, "%lf", &parameters.precision);
                if (words_read == 0) {
                    fprintf(stderr, "Couldn't read input, using default value for precision\n");
                }
                break;
            default:
                puts("Unrecognized flag ... abort\n");
                exit(EXIT_FAILURE);
        }
    }
    if (parameters.dimension == 0 || parameters.agents_count == 0) {
        puts("Missing either dimension or agents_count, cannot proceed.");
        exit(EXIT_FAILURE);
    }

    printf("**********************************\n");
    printf(" Starting parameters: \n\n");
    printf("  agents count = %d\n", parameters.agents_count);
    printf("  dimension    = %d\n", parameters.dimension);
    printf("  precision    = %lf\n", parameters.precision);
    printf("**********************************\n");

    /* unsigned int local_agents_count = (unsigned int)ceil(agents_count / (double)p); */

    printf("**********************************\n");
    printf(" funcall test: \n\n");
    printf("    test call ret val = %f\n", funcall_test(ackley, NULL));
    printf("**********************************\n");

    printf("**********************************\n");
    printf(" start search : \n\n");
    PSO_range range  = {-5, 5};
    PSO_state * result = pso_search(ackley, &range, &parameters);
    printf("   pso search result = %lf\n", result->val);
    printf("**********************************\n");

    /* release heap */ 
    result = reset_state(result);
    return 0;
}
