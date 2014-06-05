function visualize(fn, xrange, yrange)
    [X, Y] = meshgrid(xrange);
    [row, col] = size(X);
    Z = zeros(row, col);
    for r=1:row
        for c=1:col
            Z(r, c) = fn([X(r, c), Y(r, c)]);
        end
    end
    % Z = arrayfun(@(x, y) fn([x, y]), X, Y);
    grid on
    surface(X, Y, Z);
end
