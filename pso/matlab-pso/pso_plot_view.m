function frames = pso_plot_view(parameters, pso_status, i, frames)
    scatter([parameters.dim_range(1,1) parameters.dim_range(1,2)], ...
            [parameters.dim_range(2,1) parameters.dim_range(2,2)], '.');
    scatter(pso_status.pos(1, :), pso_status.pos(2, :), 'b');
    frames(i) = getframe;
end
