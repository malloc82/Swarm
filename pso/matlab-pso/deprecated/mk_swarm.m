function [swarm_fn agents_update] = mk_swarm(fn, w, a1, a2) % add v_max
    local_best_pos  = [];
    local_best_vals = [];
    global_best_pos = [];
    global_best_val = 0;

    function [new_pos new_v best_pos best_val] = swarm_update(pos, v, v_max)
        [dim, agent_count] = size(pos);
        update = 0;

        % find local best
        if isempty(local_best_pos)
            local_best_pos     = pos;
            local_best_vals    = zeros(1, agent_count);
            update = 1;
            for c=1:agent_count
                local_best_vals(c) = fn(pos(:, c)');
            end
            % local_best_vals
        else
            for c=1:agent_count
                val = fn(pos(:,c)');
                if val < local_best_vals(c)
                    update = 1;
                    local_best_vals(c)  = val;
                    local_best_pos(:,c) = pos(:,c);
                end
            end
        end

        % find global best
        if update > 0
            [m, i] = min(local_best_vals);
            global_best_val = m;
            global_best_pos = local_best_pos(:, i);
        end

        % update swarm
        new_pos = pos + v;
        new_v = zeros(dim, agent_count);
        for i=1:agent_count
            new_v(:, i) = v(:, i)*w + ...
                          a1*rand()*(local_best_pos(:, i) - pos(:, i)) + ...
                          a2*rand()*(global_best_pos - pos(:, i));
        end
        % new_v   = v.*w + ...
        %           a1*rand()*(local_best_pos  - pos) + ...
        %           a2*rand()*(repmat(global_best_pos, [1 agent_count]) - pos);
        for d=1:agent_count
            new_v_norm = norm(new_v(:, d));
            if new_v_norm > v_max
                new_v(:, d) = (v_max/new_v_norm).*new_v(:,d);
            end
        end
        best_pos = global_best_pos;
        best_val = global_best_val;
    end

    function agents_update_fn(delete_mask)
        local_best_pos  = local_best_pos(:, logical(delete_mask));
        local_best_vals = local_best_vals(logical(delete_mask));
    end
    % function reset_local_fn()
    %     local_best_pos  = [];
    %     local_best_vals = [];
    % end

    swarm_fn      = @swarm_update;
    agents_update = @agents_update_fn;
    reset_local   = @reset_local_fn;
end
