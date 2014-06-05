function [test_fn reset_a_fn reset_c_fn] = closure_test(a, b)
    c = ones(2, 2);
    function y = fn(d)
        a
        b = c + 2
        c
        d
        y = a + b + c + d;
    end
    function reset_a() 
        a = 0;
    end 
    function reset_c(new_c) 
        c = new_c;
    end 
    
    test_fn = @fn;
    reset_a_fn = @reset_a;
    reset_c_fn = @reset_c;
end
