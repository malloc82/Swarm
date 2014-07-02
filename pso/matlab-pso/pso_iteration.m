function pso_status = pso_iteration(fn, parameters, pso_status)
    pso_status.pos = pso_status.pos + pso_status.v;
    for i=1:parameters.agents_count
        v = parameters.w  * pso_status.v(:, i) + ...
            parameters.a1 * rand() * (pso_status.best_pos(:, i) - pso_status.pos(:, i)) + ...
            parameters.a2 * rand() * (pso_status.global_best_pos - pso_status.pos(:, i));
        scale = pso_status.v_max / norm(v);
        if scale < 1
            pso_status.v(:, i) = v.*scale;
        else
            pso_status.v(:, i) = v;
        end
    end

    pso_status.sd_pos = arrayfun(@(d) std(pso_status.pos(d, :)), (1:pso_status.dim));
    pso_status.v_max  = new_v_max(pso_status.pos, pso_status.dim, pso_status.v_max);

    update = 0;
    for i=1:parameters.agents_count
        val = fn(pso_status.pos(:, i)');
        if val < pso_status.best_val(i)
            update = update + 1;
            pso_status.best_val(i) = val;
            pso_status.best_pos(:, i) = pso_status.pos(:, i);
        end
    end
    if update > 0
        [m , i] = min(pso_status.best_val);
        pso_status.global_best_val = m;
        pso_status.global_best_pos = pso_status.best_pos(:, i);
    end
end
