%% ackley function
% range: [-32 32]

ackley_fn = mk_ackley(20, 0.2, 2*pi);
% best_vals = []; 
% best_pos  = [];
% fprintf('iteration: ');

display('start testing ackley function ...');

%% 5 Dimension test
% for i=1:50
%     fprintf('d...', i);
%     [v, p] = swarm_run(ackley_fn, ...
%                        [-32, 32; 
%                         -32, 32; 
%                         -32, 32; 
%                         -32, 32; 
%                         -32, 32], 1500, 0.01);
%     best_vals = [best_vals; v];
%     best_pos  = [best_pos;  p];
%     fprintf('f  [%f %f %f %f %f]', v, p);
%     fprintf('\n');
% end


%% 2 Dimension test
for i=1:50
    fprintf('%d...', i);
    [v, p] = swarm_run(ackley_fn, ...
                       [-32, 32; 
                        -32, 32], 100, 0.01);
    best_vals = [best_vals; v];
    best_pos  = [best_pos;  p];
    fprintf('f : [%f %f]', v, p);
    fprintf('\n');
end

plot((1:length(best_vals)), best_vals, 'r');
