function test_rastrigin(iterations)
%% rastrigin function
% range: [-5 5]

    best_vals = []; 
    best_pos  = [];
    display('start ... ');
    error_results = 0;
    for i=1:iterations
        fprintf('%d ... ', i);
        [v, p] = swarm_run(@rastrigin, ...
                           [-5, 5; 
                            -5, 5;], 200, 0.01);
        best_vals = [best_vals; v];
        best_pos  = [best_pos;  p];
        fprintf('%f : [%f %f], ', v, p);
        if v > 0.5, error_results = error_results + 1; end
        fprintf('error = %d', error_results);
        fprintf('\n');
    end
    display('end. ');
    plot((1:length(best_vals)), best_vals, 'r');
end 
