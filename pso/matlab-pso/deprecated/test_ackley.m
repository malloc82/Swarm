function test_ackley(agents_count, dimensions, iterations)
% for testing ackley function 
    if nargin < 3
        display('default iterations = 50');
        iterations = 50;
        if nargin < 2
            display('default dimensions = 2');
            dimensions = 2;
        end 
    end
    ackley_fn = mk_ackley(20, 0.2, 2*pi);
    best_vals = []; 
    best_pos  = [];

    display('start testing ackley function ...');
    fprintf('dimensions = %d\n', dimensions);
    fprintf('iterations = %d\n', iterations);

    dimensions_ranges = repmat([-32, 32], dimensions, 1);
    for i=1:iterations
        fprintf('%d...', i);
        [v, p] = swarm_run(ackley_fn, dimensions_ranges, agents_count, 0.01);
        best_vals = [best_vals; v];
        best_pos  = [best_pos;  p];
        fprintf('%f : [%f %f]', v, p);
        fprintf('\n');
    end
    display('end.');
    plot((1:length(best_vals)), best_vals, 'r');
end