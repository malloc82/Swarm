#include "test_fns.h"
#include "io.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <getopt.h>

static struct option input_options[] = {
    {"dimension",    required_argument, 0, 'n'},
    {"data",         required_argument, 0, 'd'},
    {0, 0, 0, 0}
};

int main(int argc, char *argv[])
{
    int c, longindex;
    size_t n = 0;
    double * data = NULL;
    size_t data_str_len = 0;
    char * data_str = NULL;

    while ((c = getopt_long(argc, argv, "n:d:m:", input_options, &longindex)) != -1) {
        switch(c) {
            case 'm':
                read_parameter_double(optarg, &ackley_c, "michalewicz_m");
                break;
            case 'n':
                read_parameter_size_t(optarg, &n, "data dimension");
                break;
            case 'd':
                data_str_len = strlen(optarg) + 1;
                data_str     = alloca(sizeof(char) * data_str_len);
                strncpy(data_str, optarg, data_str_len);
                break;
            default:
                fprintf(stderr, "Unrecognized flag %c ... abort\n", c);
                exit(EXIT_FAILURE);
        }
    }

    if (!data) {
        if (data_str && n > 0) {
            read_parameter_data_double(data_str, &data, n);
        } else {
            fprintf(stderr, "Error: not enough info. quite.\n");
            exit(EXIT_FAILURE);
        }
    }
    pso_print_result(0, data, n, michalewicz(data, n));
    free(data);
    return 0;
}
