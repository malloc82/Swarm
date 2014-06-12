function test_rastrigin(agents_count, accuracy, dimensions, iterations)
%% rastrigin function
% range: [-5 5]
    if nargin < 3
        display('default iterations = 50');
        iterations = 50;
        if nargin < 2
            display('default dimensions = 2');
            dimensions = 2;
        end 
    end

    best_vals = []; 
    best_pos  = [];
    
    display('start ... ');
    fprintf('dimensions = %d\n', dimensions);
    fprintf('iterations = %d\n', iterations);
    
    error_results = 0;
    dimensions_ranges = repmat([-5, 5], dimensions, 1);
    
    % format 
    format = '%12.6f : [';
    for i=1:dimensions
        format = strcat(format, ' %11.6f');
    end
    format = strcat(format, '  ],');

    for i=1:iterations
        fprintf('%3.d ... ', i);
        
        t = cputime;
        [v, p] = swarm_run(@rastrigin, dimensions_ranges, agents_count, accuracy);
        elapsed_time = cputime - t;
        
        best_vals = [best_vals; v];
        best_pos  = [best_pos;  p];
                
        fprintf(format, v, p);
        if v > 0.5, error_results = error_results + 1; end
        fprintf('  error = %3.d,  elapsed time = %.2fs\n', error_results, elapsed_time);
    end
    display('end. ');
    plot((1:length(best_vals)), best_vals, 'r');
end 
