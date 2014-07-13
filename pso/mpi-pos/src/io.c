#include "io.h"
#include <errno.h>

size_t read_parameter_size_t(const char * input, const char * name) {
    if (!input) {
        fprintf(stderr, "Error: input is NULL while reading %s. quit.", name);
#ifdef PSO_MPI
        MPI_Finalize();
#endif
        exit(EXIT_FAILURE);
    }

    char * endptr;
    size_t val;
    errno = 0;
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
    return val;
}

double read_parameter_double(const char * input, const char * name) {
    if (!input) {
        fprintf(stderr, "Expecting argument for %s, not found. quit.\n", name);
#ifdef PSO_MPI
        MPI_Finalize();
#endif
        exit(EXIT_FAILURE);
    }

    int items_read = 0;
    double val;
    items_read = sscanf(input, "%lf", &val);
    if (items_read == 0) {
        fprintf(stderr, "Couldn't read input for %s... quit.\n", name);
#ifdef PSO_MPI
        MPI_Finalize();
#endif
        exit(EXIT_FAILURE);
    }
    return val;
}

void read_parameter_range(const char * input, PSO_parameters * parameters)
{
    if (!input) {
        fprintf(stderr, "Expecting argument for ranges, not found. quit.\n");
#ifdef PSO_MPI
        MPI_Finalize();
#endif
        exit(EXIT_FAILURE);
    }

    size_t items_read = 0, i = 0, input_len = strlen(input) + 1;
    char * token = NULL;
    char * input_str = malloc(sizeof(char) * input_len);
    strncpy(input_str, input, input_len);
    /* Finding out dimensions */
    for (i = 0, token = strtok(input_str, "; "); token != NULL; ++i, token = strtok(NULL, "; "));
    strncpy(input_str, input, input_len); /* reset */

    parameters->dimension = i;
    parameters->ranges = malloc(sizeof(PSO_range)*i);

    for (i = 0, token = strtok(input_str, ";"); token != NULL; ++i, token = strtok(NULL, ";")) {
        items_read = sscanf(token, "%lf,%lf", &parameters->ranges[i].lo, &parameters->ranges[i].hi);
        if (items_read != 2) {
            fprintf(stderr, "Error reading range info, i = %d. abort.\n", i);
            free(input_str);
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
    free(input_str);
    return;
}

void read_parameter_data_double(const char * input,  double ** data, const size_t n)
{
    if (!input) {
        fprintf(stderr, "Expecting argument for ranges, not found. quit.\n");
#ifdef PSO_MPI
        MPI_Finalize();
#endif
        exit(EXIT_FAILURE);
    }

    size_t items_read = 0, i = 0, input_len = strlen(input) + 1;
    char * token     = NULL;
    char * input_str = malloc(sizeof(char) * input_len);
    strncpy(input_str, input, input_len);
    *data = malloc(sizeof(double)*n);
    for (i = 0, token = strtok(input_str, ", ");
         token != NULL && i < n;
         ++i, token = strtok(NULL, ", ")) {
        items_read = sscanf(token, "%lf", (*data)+i);
        if (items_read != 1) {
            fprintf(stderr, "Error reading range info, i = %d. abort.\n", i);
            free(input_str);
#ifdef PSO_MPI
            MPI_Finalize();
#endif
            exit(EXIT_FAILURE);
        }
    }
    free(input_str);
    if (i != n) {
        fprintf(stderr, "Reading ranges: only %d elements are read, incomplete data.\n", i);
    }
    return;
}

func_type read_parameter_func_type(const char * input, const char * name)
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

void print_double_vec(const char * name, const double * vec, const size_t n)
{
    size_t i;
    if (name)
        printf("%s : [%lf", name, vec[0]);
    else
        printf("[%lf", vec[0]);

    for (i = 1; i < n; ++i)
        printf(", %lf", vec[i]);
    puts("]");
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
