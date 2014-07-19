#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

extern char * optarg;

static struct option input_options[] = {
    {"id", required_argument, 0, 'd'},
    {0,0,0,0}
};

/* int * setup_neighbors(const int id, const int p, size_t * count) */
/* { */
/*     if (id >= 0 && p > 0) { */
/*         int * neighbors = malloc(sizeof(int) * 4); */

/*         const int width   = ceil(sqrt(p)); */
/*         const int last_id = p - 1; */
/*         const int row     = id / width; */
/*         const int col     = id % width; */
/*         const int max_row = last_id / width; */
/*         const int max_col = last_id % width; */

/*         /\* printf("\n width = %d", width); *\/ */
/*         /\* printf("\n row = %d, col = %d", row, col); *\/ */
/*         /\* printf("\n max_row = %d, max_col = %d", max_row, max_col); *\/ */

/*         *count = 0; */
/*         /\* up *\/ */
/*         if (row == 0) { */
/*             if (col <= max_col) { */
/*                 neighbors[*count] = max_row * width + col; */
/*             } else { */
/*                 neighbors[*count] = (max_row - 1) * width + col; */
/*             } */
/*         } else { */
/*             neighbors[*count] = (row - 1) * width + col; */
/*         } */
/*         (*count) += (neighbors[*count] == id) ? 0 : 1; /\* update count *\/ */

/*         /\* down *\/ */
/*         if (row == max_row || col > max_col) { */
/*             neighbors[*count] = col; */
/*         } else { */
/*             neighbors[*count] = (row + 1) * width + col; */
/*         } */
/*         (*count) += (neighbors[*count] == id || */
/*                      (*count != 0 && neighbors[(*count)-1] == neighbors[*count])) ? 0 : 1; */

/*         /\* left *\/ */
/*         if (col == 0) { */
/*             neighbors[*count] = (row < max_row) ? (row + 1) * width - 1 : last_id; */
/*         } else { */
/*             neighbors[*count] = row * width + (col - 1); */
/*         } */
/*         (*count) += (neighbors[*count] == id || */
/*                      (*count != 0 && neighbors[(*count)-1] == neighbors[*count])) ? 0 : 1; */

/*         /\* right *\/ */
/*         if ((col == width - 1) || (row == max_row && id == last_id)) { */
/*             neighbors[*count] = row * width; */
/*         } else { */
/*             neighbors[*count] = row * width + col + 1; */
/*         } */
/*         (*count) += (neighbors[*count] == id || */
/*                      (*count != 0 && neighbors[(*count)-1] == neighbors[*count])) ? 0 : 1; */

/*         size_t i; */
/*         for (i = *count; i < 4; ++i) { */
/*             neighbors[i] = -1; */
/*         } */
/*         /\* printf("\n neighbors: %d", neighbors[0]); *\/ */
/*         /\* size_t i; *\/ */
/*         /\* for (i = 1; i < 4; ++i) { *\/ */
/*         /\*     if (neighbors[i] >=0 ) *\/ */
/*         /\*         printf(", %d", neighbors[i]); *\/ */
/*         /\* } *\/ */
/*         /\* puts("\n"); *\/ */
/*         return neighbors; */
/*     } else { */
/*         printf("\n Failure: Id needs to be non-negative, p needs to be positive \n"); */
/*         return NULL; */
/*     } */
/* } */

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
    char   test_str[64];
    char   space_str[64];
    size_t test_str_len;
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
    } else {
        printf("\n %s Failure: id = %d, p = %d, error = %d", test_str, obj->id, obj->p, error);
        printf("\n %*s expected: (%d)", test_str_len, " ", obj->count);
        for (i = 0; i < obj->count; ++i) {
            printf(" %d", obj->neighbors[i]);
        }
        printf("\n %*s      got: (%d)", test_str_len, " ", count);
        for (i = 0; i < count; ++i) {
            printf(" %d", neighbors[i]);
        }
    }
    if (neighbors)
        free(neighbors);
    return;
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
