#include "pso_mpi.h"

#include "pso.h"
#include "test_fns.h"
#include "io.h"

#include <getopt.h>
#include <mpi.h>

static struct option pso_options[] = {
    {"fn",           required_argument, 0, 'f'},
    {"dimension",    required_argument, 0, 'd'},
    {"ranges",       required_argument, 0, 'r'},
    {"agents_count", required_argument, 0, 'n'},
    {"precision",    required_argument, 0, 'p'},
    {"max_runs",     required_argument, 0, 'i'},
    {"w",            required_argument, 0, 'w'},
    {"a1",           required_argument, 0, 'a'},
    {"a2",           required_argument, 0, 'b'},
    {"test_runs",    required_argument, 0, 't'},
    {0, 0, 0, 0}
};

int main(int argc, char *argv[])
{
    int id = -1;
    int p  = 0;
    int c, longindex, verbose = 0;
    func_type fn = NULL;
    PSO_parameters parameters = {-1, 0};
    TEST_PROFILER profiler = new_profiler(0, 1);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &parameters.id);
    MPI_Comm_size(MPI_COMM_WORLD, &parameters.p);
    pso_mpi_init(&parameters);

    while ((c = getopt_long(argc, argv, "w:a:b:", pso_options, &longindex)) != -1) {
        switch (c) {
            case 'f': /* function select */
                fn = read_parameter_func_type(optarg, "function");
                break;
            case 'd': /* dimension */
                if (!parameters.ranges){
                    parameters.dimension = read_parameter_size_t(optarg, "dimension");
                }
                break;
            case 'r': /* ranges */
                read_parameter_range(optarg, &parameters);
                break;
            case 'n': /* agents count */
                parameters.agents_count = read_parameter_size_t(optarg, "agents count");
                break;
            case 'p': /* precision */
                parameters.precision = read_parameter_double(optarg, "precision");
                break;
            case 'i': /* max iterations */
                parameters.max_runs = read_parameter_size_t(optarg, "max runs");
                break;
            case 'w':
                parameters.w = read_parameter_double(optarg, "w");
                break;
            case 'a': /* a1 */
                parameters.a1 = read_parameter_double(optarg, "a1");
                break;
            case 'b': /* a2 */
                parameters.a2 = read_parameter_double(optarg, "a2");
                break;
            case 't':
                profiler_update_runs(&profiler, read_parameter_size_t(optarg, "test runs"));
                break;
            case 'e':
                profiler.expected = read_parameter_double(optarg, "expected");
                break;
            case 'v':
                verbose = 1;
                break;
            default:
                fprintf(stderr, "Unrecognized flag %c ... abort\n", c);
                exit(EXIT_FAILURE);
        }
    }

    if (!fn) {
        fprintf(stderr, "Need to specify a function to optimize\n");
        MPI_Finalize();
        exit(EXIT_FAILURE);
    }

    print_parameters(&parameters);

    printf("*********************************************************************\n");

    clear_parameters(&parameters);
    MPI_Finalize();

    return 0;
}
