#include "pso.h"
#include "test_fns.h"
#include "io.h"
#include "profiler.h"

#include <getopt.h>

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
    {"verbose",      no_argument,       0, 'v'},
    {"expected",     required_argument, 0, 'e'},
    {0, 0, 0, 0}
};

int main(int argc, char *argv[])
{
    int c, longindex, verbose = 0;
    func_type fn = NULL;
    PSO_parameters parameters = {0, 0, 0, 0, 0, 0, 0, 0};
    TEST_PROFILER profiler = new_profiler(0, 1);

    while ((c = getopt_long(argc, argv, "w:a:b:v", pso_options, &longindex)) != -1) {
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
        exit(EXIT_FAILURE);
    }

    print_parameters(&parameters);
    printf("*********************************************************************\n");
    printf(" start search : \n\n");
    for (profiler.completed = 0; profiler.completed < profiler.total_runs;) {
        PSO_status result = pso_search(fn, &parameters);
        update_pso_profiler(&profiler, &result);
        /* printf("   pso search (%lu) result = %lf, ", i, result.val_best); */
        /* print_double_vec("pos", result.pos_best, parameters.dimension); */
        if (verbose)
            pso_print_result(profiler.completed, result.pos_best, parameters.dimension, result.val_best);
        clear_status(&result, &parameters);
    }

    printf("*********************************************************************\n");

    profiler_report(&profiler);
    clear_parameters(&parameters);
    release_profiler(&profiler);
    return 0;
}
