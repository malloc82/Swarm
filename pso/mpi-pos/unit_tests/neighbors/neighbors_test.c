#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "pso_comm.h"

extern char * optarg;

static struct option input_options[] = {
    {"id", required_argument, 0, 'd'},
    {0,0,0,0}
};

typedef struct {
    int id;
    int p;
    size_t count;
    int neighbors[4];
} Test_obj;

void print_test_obj(const Test_obj * obj)
{
    printf("\n id = %d, total = %d", obj->id, obj->p);
    printf(",  Neighbors: ");
    if (obj->count == 0) {
        printf("none");
    } else {
        size_t i;
        printf("  %d", obj->neighbors[0]);
        for (i = 1; i < obj->count; ++i) {
            printf(", %d", obj->neighbors[i]);
        }
    }
    puts("\n");
    return;
}

int check_test_case(const int test_id, const Test_obj * obj)
{
    int error = 0;
    size_t count, i;
    int * neighbors = setup_neighbors(obj->id, obj->p, &count);
    char test_str[64];
    char space_str[64];
    int  test_str_len;
    int  retval = 1;
    sprintf(test_str, "==> test case (%03d): id = %03d, p = %03d ::: ", test_id, obj->id, obj->p);
    test_str_len = strlen(test_str);

    /* printf("test_str_len = |%s|, len = %lu\n", test_str, test_str_len); */
    /* printf("               |%*s|\n", test_str_len, " "); */

    if (count == obj->count) {
        if (count != 0) {
            for (i = 0; i < count; ++i) {
                if (obj->neighbors[i] != neighbors[i]) {
                    error += 1;
                }
            }
        }
    } else {
        error += 1;
    }
    if (error == 0) {
        printf("\n %s Success: id = %d, p = %d", test_str, obj->id, obj->p);
        retval = 0;
    } else {
        printf("\n %s Failure: id = %d, p = %d, error = %d", test_str, obj->id, obj->p, error);
        printf("\n %*s expected: (%lu)", test_str_len, " ", obj->count);
        for (i = 0; i < obj->count; ++i) {
            printf(" %d", obj->neighbors[i]);
        }
        printf("\n %*s      got: (%lu)", test_str_len, " ", count);
        for (i = 0; i < count; ++i) {
            printf(" %d", neighbors[i]);
        }
        retval = 1;
    }
    if (neighbors)
        free(neighbors);
    return retval;
}

int main(int argc, char *argv[])
{
    int id = -1, p = 0;
    int longindex;
    char c;
    size_t count;
    while ((c = getopt_long(argc, argv, "p:h", input_options, &longindex)) != -1) {
        switch (c) {
            case 'd':
                sscanf(optarg, "%d", &id);
                break;
            case 'p':
                sscanf(optarg, "%d", &p);
                break;
            default:
                printf("\n Usage: ");
                printf("\n     --id id");
                printf("\n     -p    p");
                printf("\n");
                exit(0);
        }
    }

    /* printf("\n id = %d,  p = %d ", id, p); */
    /* int * neighbors = setup_neighbors(id, p, &count); */
    /* if (neighbors) free(neighbors); */

    Test_obj test_cases[] = {{0, 1, 0, -1, -1, -1, -1},
                             {0, 2, 1,  1, -1, -1, -1},
                             {1, 2, 1,  0, -1, -1, -1},
                             {0, 3, 2,  2,  1, -1, -1},
                             {1, 3, 1,  0, -1, -1, -1},
                             {2, 3, 1,  0, -1, -1, -1},
                             {0, 4, 2,  2,  1, -1, -1},
                             {1, 4, 2,  3,  0, -1, -1},
                             {2, 4, 2,  0,  3, -1, -1},
                             {3, 4, 2,  1,  2, -1, -1},
                             {0, 5, 3,  3,  2,  1, -1},
                             {1, 5, 3,  4,  0,  2, -1},
                             {2, 5, 2,  1,  0, -1, -1},
                             {3, 5, 2,  0,  4, -1, -1},
                             {4, 5, 2,  1,  3, -1, -1},
                             {0, 6, 3,  3,  2,  1, -1},
                             {1, 6, 3,  4,  0,  2, -1},
                             {2, 6, 3,  5,  1,  0, -1},
                             {3, 6, 3,  0,  5,  4, -1},
                             {4, 6, 3,  1,  3,  5, -1},
                             {5, 6, 3,  2,  4,  3, -1},
                             {0, 7, 4,  6,  3,  2,  1},
                             {1, 7, 3,  4,  0,  2, -1},
                             {2, 7, 3,  5,  1,  0, -1},
                             {3, 7, 4,  0,  6,  5,  4},
                             {4, 7, 3,  1,  3,  5, -1},
                             {5, 7, 3,  2,  4,  3, -1},
                             {6, 7, 2,  3,  0, -1, -1},
                             {0, 8, 4,  6,  3,  2,  1},
                             {1, 8, 4,  7,  4,  0,  2},
                             {2, 8, 3,  5,  1,  0, -1},
                             {3, 8, 4,  0,  6,  5,  4},
                             {4, 8, 4,  1,  7,  3,  5},
                             {5, 8, 3,  2,  4,  3, -1},
                             {6, 8, 3,  3,  0,  7, -1},
                             {7, 8, 3,  4,  1,  6, -1},
                             {0, 0, 0, 0, 0, 0, 0}};
    size_t i;
    for (i = 0;
         !(test_cases[i].id    == 0 &&
           test_cases[i].p     == 0 &&
           test_cases[i].count == 0);
         ++i) {
        /* print_test_obj(test_cases + i); */
        check_test_case(i, test_cases + i);
    }
    puts("");
    return 0;
}
