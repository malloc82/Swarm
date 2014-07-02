function v = v_max_fn(s)
    if s > 1
        v = log(s + 1);
    else
        v = log(s^2 + 1);
    end
end
