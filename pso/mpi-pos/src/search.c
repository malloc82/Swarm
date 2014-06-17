#include "pso.h"

int pso_update_state(const PSO_state *      agents_states, 
                     PSO_state *            global, 
                     const PSO_parameters * parameters)
{
    int i, best_index = -1;
    size_t data_size = parameters->dimension * sizeof(double);
    for (i = 0; i < parameters->agents_count; ++i) {
        if (agents_states[i].val < global->val) {
            best_index = i;
        }
    }
    if (best_index >= 0) {
        global->val = agents_states[best_index].val;
        memcpy(agents_states[best_index].pos, global->pos, data_size);
    }
    return 0;
}

int pso_walk(double **              agents_pos, 
             PSO_state *            agents_states, 
             const PSO_parameters * parameters,
             double (*fn)(const double *, const int))
{
    
}

PSO_state * pso_search(double (*fn)(const double *, const int), 
                       const PSO_range * range, 
                       const PSO_parameters * parameters)
{
    int n, d;
    double **   agents_pos    = new_agents_pos   (parameters->agents_count, parameters->dimension);
    PSO_state * agents_states = new_agents_states(parameters->agents_count, 
                                                  parameters->dimension, 
                                                  range, 
                                                  fn);
    PSO_state * optm_state = malloc(sizeof(PSO_state));
    optm_state->pos = rand_array_fixed_range(range->lo, range->hi, parameters->dimension);
    optm_state->val = fn(optm_state->pos, parameters->dimension);
    
    /* while (1) { */
    /*     pso_update_state(agents_states, &best, parameters); */
    /*     /\* pso_move(agents_pos, agents_state,  *\/ */
        
    /* } */
    
    agents_pos    = release_agents_pos(agents_pos, parameters->agents_count);
    agents_states = release_agents_states(agents_states, parameters->agents_count);
    return optm_state;
}
