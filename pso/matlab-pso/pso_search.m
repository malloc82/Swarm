function [best_val, best_pos] = pso_search(fn, dim_range, agents_count, accuracy, debug)
    if nargin < 5 
        debug = 0; 
    end
    max_runs = 1000;
    [dim, ~] = size(dim_range);

    [swarm agents_update] = mk_swarm(fn, 1, 1, 2);

    pos    = shuffle_pos(dim_range, agents_count);
    sd_pos = arrayfun(@(d) std(pos(d, :)), (1:dim));
    v_max  = new_v_max(pos, dim);
    v      = init_v(dim_range, agents_count, v_max);

    for i=1:max_runs
        [next_pos next_v best_pos best_val] = swarm(pos, v, v_max);
        pos   = next_pos;
        v     = next_v;
        v_max = new_v_max(pos, dim, v_max);
    end

    if debug == 1
        fprintf('\n\n');
        pso_print_result(best_val, best_pos);
        fprintf('\n\n');
    end
end
