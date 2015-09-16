function pso_status = pso_init(fn, parameters)
    pso_status = struct();

    [pso_status.dim, ~] = size(parameters.dim_range);
    pso_status.pos      = shuffle_pos(parameters.dim_range, parameters.agents_count);
    pso_status.sd_pos   = arrayfun(@(d) std(pso_status.pos(d, :)), (1:pso_status.dim));
    pso_status.v_max    = new_v_max(pso_status.sd_pos);
    pso_status.v        = init_v(parameters.dim_range, parameters.agents_count, pso_status.v_max);

    pso_status.best_pos = pso_status.pos;
    pso_status.best_val = zeros(1, parameters.agents_count);
    for i=1:parameters.agents_count
        pso_status.best_val(i) = fn(pso_status.pos(:, i)');
    end

    [m , i] = min(pso_status.best_val);
    pso_status.global_best_val = m;
    pso_status.global_best_pos = pso_status.best_pos(:, i);
end
