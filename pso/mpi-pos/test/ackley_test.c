#include "pso.h"
#include <unistd.h>

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
    double input[] = {3,5,7};
    printf("ackley function value = %f\n", ackley(input, 3));
    return 0;
}
