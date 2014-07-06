#include "pso.h"

double inner(const double * x, const double * y, const size_t n)
{
    double sum = 0;
    size_t i;
    for (i = 0; i < n; ++i) {
        sum += (x[i]*y[i]);
    }
    return sum;
}

double norm1(const double * v, const size_t n)
{
    int i;
    double sum = 0;
    for (i = 0; i < n; ++i) {
        const double x = v[i];
        sum += (x >= 0) ? x : -x;
    }
    return sum;
}

double norm2(const double * v, const size_t n)
{
    int i;
    double sum = 0;
    for (i = 0; i < n; ++i) {
        const double x = v[i];
        sum += x*x;
    }
    return sqrt(sum);
}

void normalize(double * v, const size_t n)
{
    if (!v && !n) return;
    double mag = norm2(v, n);
    size_t i;
    for (i = 0; i < n; ++i) {
        v[i] = v[i] / mag;
    }
    return;
}

double sd(const double * x, const size_t len)
{
    double sum = 0, avg = 0;
    size_t i;
    for (i = 0; i < len; ++i) {
        sum += x[i];
    }
    avg = sum / len;
    for (i = 0, sum = 0; i < len; ++i) {
        double Xi = (x[i] - avg);
        sum += Xi*Xi;
    }
    return sqrt(sum / len);
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

double * rand_array_varying_range(const PSO_range * ranges, const size_t len)
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
        const double lo = ranges[i].lo;
        const double hi = ranges[i].hi;
        array[i] = lo + (hi - lo)*((double)rand_vals[i]/UINT_MAX);
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

