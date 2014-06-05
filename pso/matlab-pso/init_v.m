function v = init_v(dim_range, agent_count, max_v)
    [dim, ~] = size(dim_range);
    v        = rand(dim, agent_count);
    % make sure the norm of each v is only 1/10 of v_max
    for c=1:agent_count
        % v(:, c) = (max_v/10/norm(v(:,c))).*v(:, c);
        v(:, c) = v(:, c) / norm(v(:,c));
    end
end
