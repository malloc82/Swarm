%% ackley function
% range: [-32 32]

% ackley_fn = mk_ackley(20, 0.2, 2*pi);
% best_vals = []; 
% best_pos  = [];
% fprintf('iteration: ');

% for i=1:50
%     fprintf('%d...', i);
%     [v, p] = swarm_run(ackley_fn, ...
%                        [-32, 32; 
%                         -32, 32; 
%                         -32, 32; 
%                         -32, 32; 
%                         -32, 32], 1500, 0.01);
%     best_vals = [best_vals; v];
%     best_pos  = [best_pos;  p];
% end

% % for i=1:50
% %     fprintf('%d...', i);
% %     [v, p] = swarm_run(ackley_fn, ...
% %                        [-32, 32; 
% %                         -32, 32], 100, 0.01);
% %     best_vals = [best_vals; v];
% %     best_pos  = [best_pos;  p];
% % end

% fprintf('\n');
% plot((1:length(best_vals)), best_vals, 'r');

%% michalewicz function 
% range: [0 pi]

% michalewicz = mk_michalewicz(10);
% best_vals = []; 
% best_pos  = [];
% display('start ... ');
% for i=1:10
%     fprintf('%d ... ', i);
%     [v, p] = swarm_run(michalewicz, ...
%                        [0, pi; 
%                         0, pi; 
%                         0, pi; 
%                         0, pi; 
%                         0, pi], 1500, 0.001);
%     best_vals = [best_vals; v];
%     best_pos  = [best_pos;  p];
%     fprintf('%f\n', v);
% end
% display('end. ');
% plot((1:length(best_vals)), best_vals, 'r');

% for i=1:50
%     fprintf('%d...', i);
%     [v, p] = swarm_run(michalewicz, ...
%                        [0, pi; 
%                         0, pi], 100, 0.01);
%     best_vals = [best_vals; v];
%     best_pos  = [best_pos;  p];
% end
% fprintf('\n');
% plot((1:length(best_vals)), best_vals, 'r');

