#include "test_fns.h"
#include "io.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <getopt.h>

static struct option input_options[] = {
    {"data",         required_argument, 0, 'd'},
    {0, 0, 0, 0}
};

int main(int argc, char *argv[])
{
    int c, longindex;
    size_t n = 0;
    double * data = NULL;

    while ((c = getopt_long(argc, argv, "n:d:a:b:c:", input_options, &longindex)) != -1) {
        switch(c) {
            case 'a':
                ackley_a = read_parameter_double(optarg,"ackley_a");
                break;
            case 'b':
                ackley_b = read_parameter_double(optarg, "ackley_b");
                break;
            case 'c':
                ackley_c = read_parameter_double(optarg, "ackley_c");
                break;
            case 'd':
                data = read_parameter_double_array(optarg, &n);
                break;
            default:
                fprintf(stderr, "Unrecognized flag %c ... abort\n", c);
                exit(EXIT_FAILURE);
        }
    }
    if (data) {
        pso_print_result(0, data, n, ackley(data, n));
        free(data);
    }
    return 0;
}
