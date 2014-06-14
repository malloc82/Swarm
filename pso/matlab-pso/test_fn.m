function error = test_fn(func_name, agents_count, accuracy, dimensions, iterations)
    fn_db = struct('rastrigin',   {@rastrigin, [-5, 5], 0}, ...
                   'ackley',      {mk_ackley(20, 0.2, 2*pi), [-32, 32], 0}, ...
                   'michalewicz', {mk_michalewicz(10), [0, pi], -1.801});

    if nargin == 0
        fprintf('Available functions for test:\n\n');
        display(fieldnames(fn_db))
        return
    elseif nargin < 3
        display('default iterations = 50');
        iterations = 50;
        if nargin < 2
            display('default dimensions = 2');
            dimensions = 2;
        end 
    end
    
    best_vals = []; 
    best_pos  = [];
    
    fprintf('start testing %s ... \n', func_name);
    fprintf('dimensions = %d\n', dimensions);
    fprintf('iterations = %d\n', iterations);
    
    error_results = 0;

    dimensions_ranges = repmat(getfield(fn_db(2), func_name), dimensions, 1)
    fn = getfield(fn_db(1), func_name)
    expected_val = getfield(fn_db(3), func_name);
    
    % format 
    format = '%1.6f : [';
    for i=1:dimensions
        format = strcat(format, '%11.6f');
    end
    format = strcat(format, '   ],');

    for i=1:iterations
        fprintf('%3.d ... ', i);
        
        t = cputime;
        [v, p] = swarm_run(fn, dimensions_ranges, agents_count, accuracy);
        elapsed_time = cputime - t;
        
        best_vals = [best_vals; v];
        best_pos  = [best_pos;  p];
                
        fprintf(format, v, p);
        if v > expected_val + 0.5 || v < expected_val - 0.5
            error_results = error_results + 1; 
        end
        fprintf('  error count = %3.d,  elapsed time = %.2fs\n', error_results, elapsed_time);
    end
    display('end. ');
    plot((1:length(best_vals)), best_vals, 'r');
end 
