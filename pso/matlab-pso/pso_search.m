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
    % pso_status
    for i=1:parameters.max_runs
        pso_status = pso_iteration(fn, parameters, pso_status);
        if debug == 1
            if (i == 1)
                frames = pso_plot_view(parameters, pso_status, i);
            else
                frames = pso_plot_view(parameters, pso_status, i, frames);
            end
        end
    end

    best_val = pso_status.global_best_val;
    best_pos = pso_status.global_best_pos;

    if debug == 1
        fprintf('\n\n');
        pso_print_result(best_val, best_pos);
        fprintf('\n\n');
    end
end
