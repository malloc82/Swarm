#include "profiler.h"

TEST_PROFILER new_profiler(const double expected, const size_t runs)
{
    TEST_PROFILER profiler = {0};
    profiler.total_runs    = runs;
    profiler.expected      = expected;
    profiler.calculated    = malloc(runs * sizeof(double));
    return profiler;
}

void profiler_summarize(TEST_PROFILER * profiler)
{
    profiler->success_rate = profiler->success_count / (double)profiler->completed;
    profiler->failure_rate = profiler->failure_count / (double)profiler->completed;
    profiler->average      = mean(profiler->calculated, profiler->completed);
    profiler->stddev       = sd(profiler->calculated, profiler->completed);
    return;
}

void profiler_report(const TEST_PROFILER * profiler)
{
    printf("\n ================================================");
    printf("\n  Peport:");
    printf("\n     Completed      : %lu/%lu", profiler->completed, profiler->total_runs);
    printf("\n     Expected value : %lf", profiler->expected);
    printf("\n     Success        : %lf/%lf (%lf\%)",
           profiler->success_count,
           profiler->completed,
           profiler->success_rate);
    printf("\n     Failure        : %lf/%lf (%lf\%)",
           profiler->failure_count,
           profiler->completed,
           profiler->failure_rate);
    puts("");
    printf("\n     mean           : %lf", profiler->average);
    printf("\n     stddev         : %lf", profiler->stddev);
    printf("\n ------------------------------------------------");
    puts("");
    return;
}

void merge_profiler(TEST_PROFILER * dest, const TEST_PROFILER * src)
{
    double * new_calculated = malloc((dest->total_runs + src->total_runs) * sizeof(double));
    if (new_calculated == NULL && dest->total_runs != 0) {
        puts("In function merge_profiler: out of memory");
        free(new_calculated);
        exit(EXIT_FAILURE);
    }
    memcpy(new_calculated,                    dest->calculated, dest->completed * sizeof(double));
    memcpy(new_calculated + dest->total_runs, src->calculated,  src->completed  * sizeof(double));
    free(dest->calculated);
    dest->calculated = new_calculated;

    dest->total_runs    += src->total_runs;
    dest->completed     += src->completed;
    dest->success_count += src->success_count;
    dest->failure_count += src->Failure_count;
    return;
}

void release_profiler(const TEST_PROFILER * profiler)
{
    if (profiler->calculated) {
        free(profiler->calculated);
        profiler->calculated = NULL;
    }
    return;
}
