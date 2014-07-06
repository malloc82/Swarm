#include "test_fns.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int c;
    while ((c = getopt(argc, argv, "a:b:c:")) != -1) {
        switch(c) {
            case 'a':
                sscanf(optarg, "%lf", &ackley_a);
                break;
            case 'b':
                sscanf(optarg, "%lf", &ackley_b);
                break;
            case 'c':
                sscanf(optarg, "%lf", &ackley_c);
                break;
        }
    }
    printf("\n a = %f, b = %f, c = %f\n", ackley_a, ackley_b, ackley_c);
    double input[6][2] = {{0, 1},
                          {0, 2},
                          {0, 3},
                          {1, 0},
                          {2, 0},
                          {3, 0}};
    const size_t len = 6;
    const size_t dim = 2;
    size_t i;
    printf("******************************************************\n");
    printf("*   Rastrigin function tests: \n");
    for (i = 0; i < len; ++i) {
        printf("*       [%lf, %lf] = %lf\n", input[i][0], input[i][1], rastrigin(input[i], 2));
    }
    printf("******************************************************\n");
    puts("");

    printf("******************************************************\n");
    printf("*   Ackley function tests: \n");
    for (i = 0; i < len; ++i) {
        printf("*       [%lf, %lf] = %lf\n", input[i][0], input[i][1], ackley(input[i], 2));
    }
    printf("******************************************************\n");
    puts("");

    printf("******************************************************\n");
    printf("*   Michalewicz function tests: \n");
    for (i = 0; i < len; ++i) {
        printf("*       [%lf, %lf] = %lf\n", input[i][0], input[i][1], michalewicz(input[i], 2));
    }
    printf("******************************************************\n");
    puts("");


    return 0;
}
