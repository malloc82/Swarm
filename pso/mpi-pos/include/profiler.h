#ifndef PROFILER_H
#define PROFILER_H

#include "pso.h"

typedef struct {
    /* raw data */
    size_t total_runs;
    size_t completed;
    size_t success_count;
    size_t failure_count;
    double expected;
    double * calculated;
    /* summary */
    double average;
    double stddev;
    double success_rate;
    double failure_rate;
} TEST_PROFILER;

TEST_PROFILER new_profiler(const size_t);

/* void update_profiler_rates(TEST_PROFILER *); */

/* void update_profiler_success(TEST_PROFILER *); */

/* void update_profiler_failure(TEST_PROFILER *); */

void profiler_summarize(TEST_PROFILER *);

void profiler_report(const TEST_PROFILER *);
/* for MPI tests */
void merge_profilers(TEST_PROFILER *, const TEST_PROFILER *);

void release_profiler(TEST_PROFILER *);

#endif /* PROFILER_H */
