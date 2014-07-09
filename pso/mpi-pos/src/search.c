#include "pso.h"
#include "utils.h"
#include "io.h"


PSO_status pso_init(func_type fn, const PSO_parameters * parameters)
/* Initialization, return a brand new PSO_status */
{
    size_t buffer_size = sizeof(double) * parameters->dimension;

    PSO_status swarm_status;
    swarm_status.dimension     = parameters->dimension;
    swarm_status.agents_states = init_agents(fn, parameters);
    swarm_status.sd_pos        = malloc(buffer_size);
    swarm_status.index_best    = 0;
    swarm_status.v_max         = -1;

    update_status(parameters, &swarm_status);

    return swarm_status;
}

void update_status(const PSO_parameters * parameters, PSO_status * swarm_status)
/* update standard deviation, v_max, global_best */
{
    size_t index_best = swarm_status->index_best;
    size_t i;
    for (i = 0; i < parameters->agents_count; ++i) {
        if (swarm_status->agents_states[i].val_best <= swarm_status->agents_states[index_best].val_best) {
            index_best = i;
        }
    }
    swarm_status->index_best = index_best;
    swarm_status->pos_best   = swarm_status->agents_states[index_best].pos_best; /* shadow copy */
    swarm_status->val_best   = swarm_status->agents_states[index_best].val_best;

    update_sd_pos(swarm_status->sd_pos,  swarm_status->agents_states,
                  parameters->dimension, parameters->agents_count);
    swarm_status->v_max = new_v_max(swarm_status->sd_pos, swarm_status->dimension, swarm_status->v_max);
}

void pso_iteration(func_type fn, const PSO_parameters * parameters, PSO_status * swarm_status)
{
    const size_t   dim         = parameters->dimension;
    const size_t   count       = parameters->agents_count;
    const double   w           = parameters->w;
    const double   a1          = parameters->a1;
    const double   a2          = parameters->a2;
    const double   v_max       = swarm_status->v_max;
    PSO_state * agents_states  = swarm_status->agents_states;

    const size_t buffer_size = sizeof(double) * dim;
    double * a1_rand = rand_array_fixed_range(0, 1, count);
    double * a2_rand = rand_array_fixed_range(0, 1, count);
    double * new_v   = alloca(buffer_size);
    size_t   n,i;

    for (n = 0; n < count; ++n) {
        /* compute current val & update local best */
        const double val = fn(agents_states[n].pos, dim);
        if (val < agents_states[n].val_best) {
            memcpy(agents_states[n].pos_best, agents_states[n].pos, buffer_size);
            agents_states[n].val_best = val;
        }
        for (i = 0; i < dim; ++i) {
            /* update v */
            new_v[i] =
                agents_states[n].v[i]* w +
                a1 * a1_rand[n] * (agents_states[n].pos_best[i] - agents_states[n].pos[i]) +
                a2 * a2_rand[n] * (swarm_status->pos_best[i]    - agents_states[n].pos[i]);
            /* update pos */
            agents_states[n].pos[i] = agents_states[n].pos[i] + agents_states[n].v[i];
        }
        const double scale = v_max/norm2(new_v, dim);
        if (scale < 1) {
            for (i = 0; i < dim; ++i) {
                agents_states[n].v[i] = new_v[i]*scale;
            }
        } else {
            memcpy(agents_states[n].v, new_v, buffer_size);
        }
    }
    free(a1_rand);
    free(a2_rand);
    return;
}

PSO_status pso_search(func_type fn, const PSO_parameters * parameters)
{
    PSO_status swarm_status = pso_init(fn, parameters);

    size_t i;
    for (i = 0; i < parameters->max_runs; ++i) {
        pso_iteration(fn, parameters, &swarm_status);
        update_status(parameters, &swarm_status);
    }
    return swarm_status;
}
