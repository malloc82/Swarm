function test_result = pso_test(func_name, agents_count, dimensions, accuracy, max_runs, test_runs)
    fn_db = struct('rastrigin',   {@rastrigin, [-5, 5], 0}, ...
                   'ackley',      {mk_ackley(20, 0.2, 2*pi), [-32, 32], 0}, ...
                   'michalewicz', {mk_michalewicz(10), [0, pi], -1.801});

    % setup

    test_result = struct('total_runs',   test_runs, ...
                         'best_vals',    [], ...
                         'best_pos',     [], ...
                         'elapsed_time', [], ...
                         'error_count',  0, ...
                         'success_rate', 0);

    fprintf('start testing %s ... \n', func_name);
    fprintf('dimensions = %d\n',       dimensions);
    fprintf('iterations = %d\n',       test_runs);

    parameters = struct('dim_range',    repmat(getfield(fn_db(2), func_name), dimensions, 1), ...
                        'agents_count', agents_count, ...
                        'accuracy',     accuracy, ...
                        'max_runs',     max_runs, ...
                        'w', 1, 'a1', 1, 'a2', 2);

    fn = getfield(fn_db(1), func_name);
    expected_val = getfield(fn_db(3), func_name);

    % test runs

    % string format
    format_str = '%1.6f : [';
    for i=1:dimensions
        format_str = strcat(format_str, '%11.6f');
    end
    format_str = strcat(format_str, '   ],');

    for i = 1:test_runs
        fprintf('%5.d ... ', i);

        t = cputime;
        [v, p] = pso_search(fn, parameters, 0);

        test_result.elapsed_time = [test_result.elapsed_time; cputime - t];
        test_result.best_vals    = [test_result.best_vals;    v];
        test_result.best_pos     = [test_result.best_pos;     p'];

        fprintf(format_str, v, p);
        if v > expected_val + 0.5 || v < expected_val - 0.5
            test_result.error_count = test_result.error_count + 1;
        end
        fprintf('  error count = %3.d,  elapsed time = %.2fs\n', ...
                test_result.error_count, ...
                test_result.elapsed_time(i));
    end
    test_result.success_rate = 1 - test_result.error_count / test_result.total_runs;
end
