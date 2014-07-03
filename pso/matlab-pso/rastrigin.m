function y = rastrigin(x)
    d = length(x);
    y = 10*d;
    for i=1:d
        y = y + x(i)^2 - 10*cos(2*pi*x(i));
    end
end
