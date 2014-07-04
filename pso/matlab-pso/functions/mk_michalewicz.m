function fn = mk_michalewicz(m)
    function y = michalewicz(x)
        y = 0;
        for i=1:length(x)
            xi = x(i);
            y = y - sin( xi ) * (sin( (i*xi^2)/pi ))^(2*m);
        end
    end
    fn = @michalewicz;
end
