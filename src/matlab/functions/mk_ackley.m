function fn = mk_ackley(a, b, c)
    function y = ackley(x)
        n = length(x);
        y = -a*exp(-b*sqrt(x*x'/n)) - exp(sum(arrayfun(@(x) cos(c*x), x))/n) + a + exp(1);
    end
    fn = @ackley;
end
