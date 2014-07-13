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
    size_t range_str_len = 0;
    size_t i;
    size_t test_runs = 1;
    PSO_parameters parameters = {0, 0, 0, 0, 0, 0, 0, 0};

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
                if (!optarg) {
                    fprintf(stderr, "Expecting argument for ranges, not found. quit.\n");
                    exit(EXIT_FAILURE);
                } else {
                    range_str_len = strlen(optarg) + 1;
                    range_str     = malloc(sizeof(char) * range_str_len);
                    strncpy(range_str, optarg, range_str_len);
                    read_parameter_range(range_str, &parameters);
                    free(range_str);
                }
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
                test_runs = read_parameter_size_t(optarg, "test runs");
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
