function v_max = new_v_max(sd_pos, curr_v_max)
    v_max = norm(arrayfun(@v_max_fn, sd_pos));
    % v_max = norm(arrayfun(@(d) v_max_fn(std(pos(d, :))), (1:dim)));
    if nargin == 2
        if v_max > curr_v_max
            v_max = curr_v_max;
        end
    end
end
