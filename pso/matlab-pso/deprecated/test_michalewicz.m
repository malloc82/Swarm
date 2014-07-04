function test_michalewicz(agents_count, dimensions, iterations)
    if nargin < 3
        display('default iterations = 50');
        iterations = 50;
        if nargin < 2
            display('default dimensions = 2');
            dimensions = 2;
        end 
    end

    michalewicz = mk_michalewicz(10);
    best_vals = []; 
    best_pos  = [];
    display('start testing michalewicz function ... ');
    fprintf('dimensions = %d\n', dimensions);
    fprintf('iterations = %d\n', iterations);

    % format 
    format = '%f :[';
    for i=1:dimensions
        format = strcat(format, '%f ');
    end
    format = strcat(format, '], ');
    
    dimensions_ranges = repmat([0, pi], dimensions, 1);
    for i=1:iterations
        fprintf('%d...', i);
        [v, p] = swarm_run(michalewicz, dimensions_ranges, agents_count, 0.01);
        best_vals = [best_vals; v];
        best_pos  = [best_pos;  p];
        fprintf(format, v, p);
        fprintf('\n');
    end
    display('end.');
    plot((1:length(best_vals)), best_vals, 'r');
end
