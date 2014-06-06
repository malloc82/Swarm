#include "pso.h"

double inner(double * x, double * y, const int n)
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


int randrange_array(const double * lo, 
                    const double * hi, 
                    double ** dest, 
                    const size_t len)  
{
    size_t         data_size = len*sizeof(unsigned int);
    size_t         len_written = 0;
    unsigned int * rand_vals = malloc(data_size);
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
    for (i = 0; i < len; ++i) {
        (*dest)[i] = lo[i] + (hi[i] - lo[i])*((double)rand_vals[i]/UINT_MAX);
    }
    free(rand_vals);
    return 0;
}

