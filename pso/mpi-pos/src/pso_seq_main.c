#include "pso.h"
#include "test_fns.h"
#include "io.h"

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
    {0, 0, 0, 0}
};

int main(int argc, char *argv[])
{
    int id = -1;
    int p  = 0;
    int c, longindex;
    func_type fn = NULL;
    char * range_str = NULL;
    size_t arglen = 0;
    size_t i;
    size_t test_runs = 1;
    PSO_parameters parameters = {0, 0, 0, 0, 0, 0, 0, 0};

    while ((c = getopt_long(argc, argv, "w:a:b:", pso_options, &longindex)) != -1) {
        switch (c) {
            case 'f': /* function select */
                fn = read_parameter_func_type(optarg, "function");
                break;
            case 'd': /* dimension */
                read_parameter_size_t(optarg, &parameters.dimension, "dimension");
                break;
            case 'r': /* ranges */
                if (parameters.dimension > 0) {
                    read_parameter_range(optarg, &parameters);
                } else if (!optarg) {
                    fprintf(stderr, "Expecting argument for ranges, not found. quit.\n");
                    exit(EXIT_FAILURE);
                } else {
                    arglen = strlen(optarg) + 1;
                    range_str = alloca(sizeof(char) * arglen);
                    strncpy(range_str, optarg, arglen);
                }
                break;
            case 'n': /* agents count */
                read_parameter_size_t(optarg, &parameters.agents_count, "agents count");
                break;
            case 'p': /* precision */
                read_parameter_double(optarg, &parameters.precision, "precision");
                break;
            case 'i': /* max iterations */
                read_parameter_size_t(optarg, &parameters.max_runs, "max runs");
                break;
            case 'w':
                read_parameter_double(optarg, &parameters.w, "w");
                break;
            case 'a': /* a1 */
                read_parameter_double(optarg, &parameters.a1, "a1");
                break;
            case 'b': /* a2 */
                read_parameter_double(optarg, &parameters.a2, "a2");
                break;
            case 't':
                read_parameter_size_t(optarg, &test_runs, "test runs");
                break;
            default:
                fprintf(stderr, "Unrecognized flag %c ... abort\n", c);
                exit(EXIT_FAILURE);
        }
    }
    if (!parameters.ranges) {
        if (range_str && parameters.dimension > 0) {
            read_parameter_range(optarg, &parameters);
        } else {
            fprintf(stderr, "Error: no range specified. abort");
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
    for (i = 0; i < test_runs; ++i) {
        PSO_status result = pso_search(fn, &parameters);
        /* printf("   pso search (%lu) result = %lf, ", i, result.val_best); */
        /* print_double_vec("pos", result.pos_best, parameters.dimension); */
        pso_print_result(i, result.pos_best, parameters.dimension, result.val_best);
        clear_status(&result, &parameters);
    }

    printf("*********************************************************************\n");

    clear_parameters(&parameters);

    return 0;
}
