#include "pso.h"
#include "utils.h"

double v_max_dim(const double s)
{
    return (s > 1) ? exp(s + 1) : exp(s*s + 1);
}

double new_v_max(const double * sd_pos, const size_t dim, const double curr_v_max)
{
    double * v = alloca(sizeof(double) * dim);
    size_t i;
    for (i = 0; i < dim; ++i) {
        const double s = sd_pos[i];
        v[i] = (s > 1) ? log(s + 1) : log(s*s + 1);
    }
    const double v_max = norm2(v, dim);
    return (curr_v_max > 0 && v_max >= curr_v_max) ? curr_v_max : v_max;
}

double sd_dim(const PSO_state * states, const size_t d, const size_t N)
{
    double sum = 0, u = 0;
    size_t i;
    for (i = 0; i < N; ++i) {
        sum += states[i].pos[d];
    }
    u = sum / N;
    for (i = 0, sum = 0; i < N; ++i) {
        const double x = (states[i].pos[d] - u);
        sum += x*x;
    }
    return sqrt(sum / N);
}

void update_sd_pos(double * sd_pos, const PSO_state * agents, const size_t dim, const size_t N)
{
    if (!sd_pos || !agents) return;
    size_t d;
    for (d = 0; d < dim; ++d) {
        sd_pos[d] = sd_dim(agents, d, N);
    }
    return;
}

PSO_state * init_agents(func_type fn, const PSO_parameters * parameters)
{
    size_t i;
    const size_t dim          = parameters->dimension;
    const size_t n            = parameters->agents_count;
    const size_t buffer_size  = sizeof(double) * dim;

    PSO_state * agents_states = malloc(sizeof(PSO_state) * n);

    for (i = 0; i < n; ++i) {
        agents_states[i].pos      = rand_array_varying_range(parameters->ranges, dim);
        agents_states[i].v        = rand_array_fixed_range(-1, 1, dim);
        agents_states[i].pos_best = malloc(buffer_size);
        memcpy(agents_states[i].pos_best, agents_states[i].pos, buffer_size);
        agents_states[i].val_best = fn(agents_states[i].pos_best, dim);
    }
    return agents_states;
}

PSO_state * free_agents(PSO_state * agents, const PSO_parameters * parameters)
{
    size_t i;
    const size_t n   = parameters->agents_count;
    for (i = 0; i < n; ++i) {
        free(agents[i].pos);
        free(agents[i].v);
        free(agents[i].pos_best);
    }
    free(agents);
    return NULL;
}

void clear_status(PSO_status * swarm_status, const PSO_parameters * parameters)
{
    swarm_status->agents_states = free_agents(swarm_status->agents_states, parameters);
    free(swarm_status->pos_best);
    swarm_status->pos_best      = NULL;
    free(swarm_status->sd_pos);
    swarm_status->sd_pos = NULL;
    return;
}

void clear_parameters(PSO_parameters * parameters)
{
    free(parameters->ranges);
    parameters->ranges = NULL;
}
