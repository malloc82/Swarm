#include <string.h>
#include "pso.h"

int main(int argc, char *argv[])
{
    int c;
    double lo, hi;
    int set_flag = 0;
    while ((c = getopt(argc, argv, "a:b:")) != -1) {
        switch(c) {
            case 'a':
                sscanf(optarg, "%lf", &lo);
                ++set_flag;
                break;
            case 'b':
                sscanf(optarg, "%lf", &hi);
                ++set_flag;
                break;
            default:
                fputs("Unknown flag, abort.", stderr);
                abort();
        }
    }
    if (set_flag < 2) {
        puts("Need to initialize both lo and hi\n");
        puts("quit.");
        exit(EXIT_FAILURE);
    }
    if (lo > hi) {
        double tmp = lo;
        lo = hi;
        hi = tmp;
    }
    puts("randrange() test:");
    printf("\n lo = %f, hi = %f\n", lo, hi);
    int i, j;
    for (j = 0; j < 10; ++j) {
        for (i = 0; i < 5; ++i) {
            printf("%lf, ", randrange(lo, hi));
        }
        puts("");
    }

    puts("\n\nrandrange_array() test:");
    double lo_a[10] = {lo, lo, lo, lo, lo, lo, lo, lo, lo, lo};
    double hi_a[10] = {hi, hi, hi, hi, hi, hi, hi, hi, hi, hi};
    size_t v_size = 10*sizeof(double);
    /* double *v = malloc(v_size); */
    /* memset(v, 0, v_size); */
    /* /\* double v[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; *\/ */
    /* printf("original v = "); */
    /* for (i = 0; i < 10; ++i) { */
    /*     printf("%lf, ", v[i]); */
    /* } */
    /* puts(""); */
    
    double * v = rand_array_varying_range(lo_a, hi_a, 10);
    printf("new v = ");
    for (i = 0; i < 10; ++i) {
        printf("%lf, ", v[i]);
    }
    puts("\n");
    free(v);

    return 0;
}
