function v_max = new_v_max(pos, dim, curr_v_max)
    v_max = norm(arrayfun(@(d) v_max_fn(std(pos(d, :))), (1:dim)));
    if nargin == 3
        if v_max > curr_v_max
            v_max = curr_v_max;
        end
    end
end
