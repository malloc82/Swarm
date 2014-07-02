function [best_val, best_pos, frames] = pso_search(fn, parameters, debug)
% function [best_val, best_pos] = pso_search(fn, dim_range, agents_count, accuracy, debug)
    if nargin < 3
        debug = 0;
    end

    if debug == 1
        parameters
    else
        frames = struct();
    end
    pso_status = pso_init(fn, parameters);

    [swarm agents_update] = mk_swarm(fn, 1, 1, 2);

    for i=1:parameters.max_runs
        [next_pos next_v best_pos best_val] = swarm(pos, pso_status.v, pso_status.v_max);

        pso_status.pos   = next_pos;
        pso_status.v     = next_v;
        v_max = new_v_max(pso_status.pos, dim, pso_status.v_max);

        if debug == 1
            if (i == 1)
                frames = pso_plot_view(parameters, pso_status.pos, i);
            else
                frames = pso_plot_view(parameters, pso_status.pos, i, frames);
            end
        end
    end

    if debug == 1
        fprintf('\n\n');
        pso_print_result(best_val, best_pos);
        fprintf('\n\n');
    end
end
