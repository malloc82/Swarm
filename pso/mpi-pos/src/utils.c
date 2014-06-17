#include "pso.h"

double inner(const double * x, const double * y, const int n)
{
    double sum = 0;
    int i;
    for (i = 0; i < n; ++i) {
        sum += (x[i]*y[i]);
    }
    return sum;
}

double randrange(const double lo, const double hi) {
    unsigned int rand_val;
    size_t data_size   = sizeof(unsigned int);
    size_t len_written = 0;
    int rdev = open("/dev/urandom", O_RDONLY);
    while(len_written < data_size) {
        ssize_t result = read(rdev, ((char *)&rand_val) + len_written, data_size - len_written);
        if (result < 0) {
            fputs("randrange() read failed, abort.", stderr);
            close(rdev);
            abort();
        }
        len_written += result;
    }
    close(rdev);
    /* printf("value read: %u, %u\n", rand_val, UINT_MAX); */
    return lo + (hi - lo)*((double)rand_val/UINT_MAX);
}

double * rand_array_varying_range(const double * lo, const double * hi, const size_t len)
{
    size_t         data_size   = len*sizeof(unsigned int);
    size_t         len_written = 0;
    unsigned int * rand_vals   = malloc(data_size);
    double *       array       = NULL;
    int i;
    int rdev = open("/dev/urandom", O_RDONLY);
    while (len_written < data_size) {
        ssize_t result = read(rdev, ((char *)rand_vals + len_written), data_size - len_written);
        if (result < 0) {
            fputs("randrange_array() read failed, abort.", stderr);
            close(rdev);
            abort();
        }
        len_written += result;
    }
    close(rdev);
    array = malloc(sizeof(double) * len);
    for (i = 0; i < len; ++i) {
        array[i] = lo[i] + (hi[i] - lo[i])*((double)rand_vals[i]/UINT_MAX);
    }
    free(rand_vals);
    return array;
}

double * rand_array_fixed_range(const double lo, const double hi, const size_t len)
{
    size_t         data_size   = len*sizeof(unsigned int);
    size_t         len_written = 0;
    unsigned int * rand_vals   = malloc(data_size);
    double *       array       = NULL;
    int i;
    int rdev = open("/dev/urandom", O_RDONLY);
    while (len_written < data_size) {
        ssize_t result = read(rdev, ((char *)rand_vals + len_written), data_size - len_written);
        if (result < 0) {
            fputs("randrange_array() read failed, abort.", stderr);
            close(rdev);
            abort();
        }
        len_written += result;
    }
    close(rdev);
    array = malloc(sizeof(double) * len);
    for (i = 0; i < len; ++i) {
        array[i] = lo + (hi - lo)*((double)rand_vals[i]/UINT_MAX);
    }
    free(rand_vals);
    return array;
}

double ** new_agents_pos(const size_t agents_count, const size_t dimension)
{
    int n;
    double ** agents_pos = malloc(agents_count*sizeof(double *));
    for (n = 0; n < agents_count; ++n) {
        agents_pos[n] = malloc(dimension*sizeof(double));
    }
    return agents_pos;
}

double ** release_agents_pos(double ** agents_pos, const size_t agents_count)
{
    int n;
    for (n = 0; n < agents_count; ++n) {
        free(agents_pos[n]);
    }
    free(agents_pos);
    return NULL;
}

PSO_state * new_agents_states(const size_t      agents_count,
                              const size_t      dimension,
                              const PSO_range * range,
                              double (*fn)(const double *, const int))

{
    int n;
    PSO_state * agents_states = malloc(sizeof(PSO_state) * agents_count);
    for (n = 0; n < agents_count; ++n) {
        agents_states[n].pos = rand_array_fixed_range(range->lo, range->hi, dimension);
        agents_states[n].val = fn(agents_states[n].pos, dimension);
    }
    return agents_states;
}

PSO_state * reset_state(PSO_state * agent_state)
{
    if (agent_state != NULL && agent_state->pos != NULL) {
        free(agent_state->pos);
        agent_state->pos = NULL;
    }
    free(agent_state);
    return NULL;
}

PSO_state * release_agents_states(PSO_state * agents_states, const size_t n)
{
    int i;
    for (i = 0; i < n; ++i) {
        free(agents_states[i].pos);
        agents_states[i].pos = NULL;
    }
    free(agents_states);
    return NULL;
}
