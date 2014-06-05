function [init_pos init_v] = shuffle_pos_v(dim_range, agent_count, v_max)
    [dim, ~] = size(dim_range);
    init_pos = rand(dim, agent_count);
    init_v   = rand(dim, agent_count);
    for d=1:dim
        init_pos(d, :) = ones(1, agent_count)*dim_range(d, 1) + init_pos(d, :)*(dim_range(d, 2) - dim_range(d, 1));
        init_v(d, :) = v_max(d)/10*(0.5-init_v(d, :));
    end
    for c=1:agent_count
        init_v(:, c) = init_v(:, c)/norm(init_v(:,c));
    end
end
