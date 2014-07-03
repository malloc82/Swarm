function debug_info = pso_plot_view(fn, parameters, pso_status, i, debug_info)
    if nargin == 4
        hold off
        xrange = parameters.dim_range(1, :);
        yrange = parameters.dim_range(2, :);
        [X, Y] = meshgrid(xrange(1):0.01:xrange(2), yrange(1):0.01:yrange(2));
        [row col] = size(X);
        debug_info = struct('search_space', zeros(row, col));
        for r=1:row
           for c=1:col
               debug_info.search_space(r, c) = fn([X(r, c), Y(r, c)]);
           end
        end
        debug_info.base_handle = imagesc(xrange(1):0.01:xrange(2), ...
                                         yrange(1):0.01:yrange(2), ...
                                         debug_info.search_space);
        hold on
    end
    % scatter([parameters.dim_range(1,1) parameters.dim_range(1,2)], ...
    %         [parameters.dim_range(2,1) parameters.dim_range(2,2)], '.');
    if isfield(debug_info, 'curr_scatter')
        delete(debug_info.curr_scatter);
    end
    debug_info.curr_scatter = scatter(pso_status.pos(1, :), pso_status.pos(2, :), '*', 'm');
    debug_info.frames(i) = getframe;
end
