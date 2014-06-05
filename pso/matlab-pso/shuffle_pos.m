function pos= shuffle_pos(dim_range, agent_count)
    [dim, ~] = size(dim_range);
    pos = rand(dim, agent_count);
    for d=1:dim
        pos(d, :) = ones(1, agent_count)*dim_range(d, 1) + pos(d, :)*(dim_range(d, 2) - dim_range(d, 1));
    end
end
