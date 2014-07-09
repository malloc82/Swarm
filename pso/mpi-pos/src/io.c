#include "io.h"
#include <errno.h>

void read_parameter_size_t(char       * input,
                           size_t     * var,
                           const char * name) {
    char * endptr;
    size_t val;
    errno = 0;
    if (!input) {
        fprintf(stderr, "Error: input is NULL while reading %s. quit.", name);
#ifdef PSO_MPI
        MPI_Finalize();
#endif
        exit(EXIT_FAILURE);
    }
    val = strtol(input, &endptr, 10);
    if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) ||
        (errno != 0 && val == 0))
    {
        fprintf(stderr, "strtol error while reading %s. quit.\n", name);
#ifdef PSO_MPI
        MPI_Finalize();
#endif
        exit(EXIT_FAILURE);
    }
    if (endptr == input) {
        fprintf(stderr, "No digits were found while reading %s. quite\n", name);
#ifdef PSO_MPI
        MPI_Finalize();
#endif
        exit(EXIT_FAILURE);
    }
    *var = val;
    return;
}

void read_parameter_double(char       * input,
                           double     * var,
                           const char * name) {
    int items_read = 0;
    if (!input) {
        fprintf(stderr, "Expecting argument for %s, not found. quit.\n", name);
#ifdef PSO_MPI
        MPI_Finalize();
#endif
        exit(EXIT_FAILURE);
    }
    items_read = sscanf(input, "%lf", var);
    if (items_read == 0) {
        fprintf(stderr, "Couldn't read input for %s... quit.\n", name);
#ifdef PSO_MPI
        MPI_Finalize();
#endif
        exit(EXIT_FAILURE);
    }
    return;
}

void read_parameter_range(char * input, PSO_parameters * parameters)
{
    int items_read = 0, i = 0;
    char * token = NULL;
    if (!input) {
        fprintf(stderr, "Expecting argument for ranges, not found. quit.\n");
#ifdef PSO_MPI
        MPI_Finalize();
#endif
        exit(EXIT_FAILURE);
    }
    parameters->ranges = malloc(sizeof(PSO_range)*parameters->dimension);
    for (i = 0, token = strtok(input, ";");
         token != NULL && i < parameters->dimension;
         ++i, token = strtok(NULL, ";")) {
        items_read = sscanf(token, "%lf,%lf", &parameters->ranges[i].lo, &parameters->ranges[i].hi);
        if (items_read != 2) {
            fprintf(stderr, "Error reading range info, i = %d. abort.\n", i);
#ifdef PSO_MPI
            MPI_Finalize();
#endif
            exit(EXIT_FAILURE);
        }
        if (parameters->ranges[i].lo > parameters->ranges[i].hi) {
            register double temp = parameters->ranges[i].lo;
            parameters->ranges[i].lo = parameters->ranges[i].hi;
            parameters->ranges[i].hi = temp;
        }
    }
    if (i != parameters->dimension) {
        fprintf(stderr, "Reading ranges: only %d dimensions are read, incomplete data.\n", i);
    }
    return;
}

void read_parameter_data_double(char * input,  double ** data, const size_t n)
{
    int items_read = 0, i = 0;
    char * token = NULL;
    if (!input) {
        fprintf(stderr, "Expecting argument for ranges, not found. quit.\n");
#ifdef PSO_MPI
        MPI_Finalize();
#endif
        exit(EXIT_FAILURE);
    }
    *data = malloc(sizeof(double)*n);
    for (i = 0, token = strtok(input, ", ");
         token != NULL && i < n;
         ++i, token = strtok(NULL, ", ")) {
        items_read = sscanf(token, "%lf", (*data)+i);
        if (items_read != 1) {
            fprintf(stderr, "Error reading range info, i = %d. abort.\n", i);
#ifdef PSO_MPI
            MPI_Finalize();
#endif
            exit(EXIT_FAILURE);
        }
    }
    if (i != n) {
        fprintf(stderr, "Reading ranges: only %d elements are read, incomplete data.\n", i);
    }
    return;
}

func_type read_parameter_func_type(char * input, const char * name)
{
    if (strcmp(input, "rastrigin") == 0) {
        return rastrigin;
    } else if (strcmp(input, "ackley") == 0) {
        return ackley;
    } else if (strcmp(input, "michalewicz") == 0) {
        return michalewicz;
    } else {
        fprintf(stderr, "function type is not found. quit");
#ifdef PSO_MPI
        MPI_Finalize();
#endif
        exit(EXIT_FAILURE);
    }
    return NULL;
}

void print_parameters(const PSO_parameters * parameters)
{
    size_t i;
    printf("*******************************************************************\n"
           "    Parameters:\n"
           "        dimension    = %lu\n"
           "        agents count = %lu\n"
           "        precision    = %lf\n"
           "        max runs     = %lu\n"
           "        w  = %lf\n"
           "        a1 = %lf\n"
           "        a2 = %lf\n",
           parameters->dimension,
           parameters->agents_count,
           parameters->precision,
           parameters->max_runs,
           parameters->w, parameters->a1, parameters->a2);
    if (parameters->dimension > 0) {
        puts("");
        printf("        range: %lf, %lf\n", parameters->ranges[0].lo, parameters->ranges[0].hi);
        for (i = 1; i < parameters->dimension; ++i) {
            printf("               %lf, %lf\n", parameters->ranges[i].lo, parameters->ranges[i].hi);
        }
    }
    printf("*******************************************************************\n\n");
    return;
}

void print_double_vec(const char * prefix, const double * vec, const size_t n, const char * postfix)
{
    size_t i;
    if (prefix)
        printf("%s[%lf", prefix, vec[0]);
    else
        printf("[%lf", vec[0]);

    for (i = 1; i < n; ++i)
        printf(", %lf", vec[i]);

    if (postfix)
        printf("]%s", postfix);
    else
        printf("]");
    return;
}

void pso_print_result(const size_t iteration, const double * vec, const size_t n, const double val)
{
    size_t i;
    printf("%4.lu : [%11.6lf", iteration, vec[0]);
    for (i = 1; i < n; ++i) {
        printf(",%11.6lf", vec[i]);
    }
    printf("  ] = %11.6lf\n", val);
    return;
}
