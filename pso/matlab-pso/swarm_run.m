function [best_val best_pos] = swarm_run(fn, dim_range, agent_count, std_threshold, v_max)
    function v = v_max_fn(s)
        if s > 1
            v = log(s + 1);
        else 
            v = log(s^2 + 1);
        end 
    end 
    debug = 0;
    g_ratio = (3-sqrt(5))/2;
    ratio = 0.1;
    [dim, ~] = size(dim_range);

    % bins = zeros(1, (range(2) - range(1))); %% ? 
    x_pos_std = [];
    x_pos_std_avg = [];
    x_pos_std_slope = [];

    y_pos_std = [];
    y_pos_std_avg = [];
    y_pos_std_slope = [];
    
    v_max_hist = [];
    
    % ackley_fn = mk_ackley(20, 0.2, 2*pi);
    % [swarm agents_update] = mk_swarm(ackley_fn, 1, 1, 2);

    % michalewicz = mk_michalewicz(10);
    % [swarm agents_update] = mk_swarm(michalewicz, 1, 1, 2);

    % [swarm agents_update] = mk_swarm(@rastrigin, 1, 1, 2);
    
    [swarm agents_update] = mk_swarm(fn, 1, 1, 2);
    
    pos = shuffle_pos(dim_range, agent_count);
    if nargin < 5
        v_max = norm(arrayfun(@(d) v_max_fn(std(pos(d, :))), (1:dim)));
        % v_max = norm(arrayfun(@(d) (std(pos(d, :))/27)^(1/3), (1:dim)));
    end 
    base_std = zeros(1, dim);
    for d=1:dim
        base_std(d) = std(pos(d, :));
    end 
    % v_max
    v = init_v(dim_range, agent_count, v_max);
    best_val_hist = [];
    i = 0;
    
    plot_row = 2;
    plot_col = 2;
    
    curr_std = base_std;
    for i=1:100
        % compute standard deviation for each division
        for d=1:dim
            curr_std(d) = std(pos(d, :));
        end
        
        % visualizing
        if debug == 1 && dim <= 2
            % plot positions 
            subplot(plot_row, plot_col, 1);
            scatter([dim_range(1,1) dim_range(1,2)], ...
                    [dim_range(2,1) dim_range(2,2)], '.');
            hold on
            scatter(pos(1, :), pos(2, :), 'b');
            if i > 1
                scatter(best_pos(1), best_pos(2), 'x');
            end 
            hold off
            
            % tracking best_val 
            subplot(plot_row, plot_col, 2);
            % plot((1:length(best_val_hist)), best_val_hist);
            v_max_hist = [v_max_hist v_max];
            plot((1:length(v_max_hist)), v_max_hist);
            
            subplot(plot_row, plot_col, 3);
            % x_pos_std = [x_pos_std std(pos_bins(1, :))];
            x_pos_std = [x_pos_std curr_std(1)];
            if i > 5
                % x_pos_std_avg(end) = sum(x_pos_std(end-3:end).*[0.1 0.2 0.3 0.4]);
                x_pos_std_avg = [x_pos_std_avg mean(x_pos_std(end-4:end))];
                if i > 6
                    x_pos_std_slope = [x_pos_std_slope x_pos_std_avg(end) - x_pos_std_avg(end-1)];
                else 
                    x_pos_std_slope = [x_pos_std_slope -1];
                end 

                plot((1:length(x_pos_std)), x_pos_std, 'b', ...
                     (1:length(x_pos_std_slope)), x_pos_std_slope, 'g');
                % plot((1:length(x_pos_std)), x_pos_std, 'b', ...
                %      (1:length(x_pos_std_avg)), x_pos_std_avg, 'r', ...
                %      (1:length(x_pos_std_slope)), x_pos_std_slope, 'g');
            else 
                x_pos_std_avg = [x_pos_std_avg x_pos_std(end)];
                plot((1:length(x_pos_std)), x_pos_std, 'b')
                % plot((1:length(x_pos_std)), x_pos_std, 'b', ...
                %      (1:length(x_pos_std_avg)), x_pos_std_avg, 'r');
            end 
            
            subplot(plot_row, plot_col, 4);
            % y_pos_std = [y_pos_std std(pos_bins(2, :))];
            y_pos_std = [y_pos_std curr_std(2)];
            if i > 5
                % y_pos_std_avg(end) = sum(y_pos_std(end-3:end).*[0.1 0.2 0.3 0.4]);
                y_pos_std_avg = [y_pos_std_avg mean(y_pos_std(end-4:end))];
                if i > 6
                    y_pos_std_slope = [y_pos_std_slope y_pos_std_avg(end) - y_pos_std_avg(end-1)];
                else 
                    y_pos_std_slope = [y_pos_std_slope -1];
                end 
                plot((1:length(y_pos_std)), y_pos_std, 'b', ...
                     (1:length(x_pos_std_slope)), x_pos_std_slope, 'g');
                % plot((1:length(y_pos_std)), y_pos_std, 'b', ...
                %      (1:length(y_pos_std_avg)), y_pos_std_avg, 'r', ...
                %      (1:length(x_pos_std_slope)), x_pos_std_slope, 'g');
            else 
                y_pos_std_avg = [y_pos_std_avg y_pos_std(end)];
                plot((1:length(y_pos_std)), y_pos_std, 'b')
                % plot((1:length(y_pos_std)), y_pos_std, 'b', ...
                %      (1:length(y_pos_std_avg)), y_pos_std_avg, 'r');
            end 
            
            M(i) = getframe;
            hold off
        end 

        if mean(curr_std) < std_threshold
            % msg = 'done'
            break;
        end 
        
        [next_pos next_v best_pos best_val] = swarm(pos, v, v_max);
        pos = next_pos;
        v   = next_v;
        best_val_hist = [best_val_hist best_val];

        shrink = 0;
        for d=1:dim
            if curr_std(d) / base_std(d) < ratio
                shrink = shrink + 1;
            end
        end
        if shrink == dim
            ratio = g_ratio;
            base_std = curr_std;
            debug = 0;
            msg = 'shrinking';
            shrink = 0; % reset flag
            delete_mask = ones(1, agent_count);

            new_agent_count = agent_count;
            std_thresh_hold = curr_std.*1.618;
            dim_mean = zeros(1, dim);
            for d=1:dim
                dim_mean(d) = mean(pos(d, :));
            end
            for i=1:agent_count
                for d=1:dim
                    if abs(pos(d, i) - dim_mean(d)) > std_thresh_hold(d)
                        delete_mask(i) = 0;
                        new_agent_count = new_agent_count - 1;
                        break;
                    end
                end 
                % if pos(1, i) - x_pos_mean > x_std_range || pos(2, i) - y_pos_mean > y_std_range
                %     delete_mask(i) = 0;
                %     new_agent_count = new_agent_count - 1;
                % end 
            end
            pos = pos(:, logical(delete_mask));
            v   = v(:, logical(delete_mask));
            agent_count = new_agent_count;
            agents_update(delete_mask);
        end 
        
        new_v_max = norm(arrayfun(@(d) v_max_fn(std(pos(d, :))), (1:dim)));        
        % new_v_max = norm(arrayfun(@(d) (std(pos(d, :))/27)^(1/3), (1:dim)));
        if new_v_max < v_max
            v_max = new_v_max;
        end
        

        % if sum(switch_box) > 0
        %     new_v_max = norm(arrayfun(@(d) log(std(pos(d, :)) + 1), (1:dim)));        
        %     if new_v_max < v_max
        %         v_max = new_v_max;
        %     end
        %     switch_box = zeros(1, dim);
        % end 

        % if sum(switch_box) == dim 
        %     v_max = norm(arrayfun(@(d) log(std(pos(d, :)) + 1), (1:dim)));
        %     % v_max = v_max./10
        %     switch_box = zeros(1, dim);
        % end 

        
        % x_pos_std
        % y_pos_std

        % if x_pos_std(end) > 3 && y_pos_std(end) > 3 
        %     if run_lvl == 0
        %         old_best_val = best_val;
        %         old_best_pos = best_pos;
        %     end 
        %     run_lvl = run_lvl + 1;
        %     % accuracy_lvl = accuracy_lvl - 1;
        %     if run_lvl >= accuracy_lvl
        %         msg = 'run_lvl = accuracy_lvl'
        %         run_lvl
        %         accuracy_lvl
        %         break;
        %     else
        %         if old_best_val < best_val
        %             msg = 'getting worse result, stop.'
        %             best_pos = old_best_pos
        %             best_val = old_best_val
        %             break;
        %         end
        %         best_pos
        %         best_val

        %         msg = 'new accuracy_lvl'
        %         for d=1:dim
        %             dim_range(d, :) = [min(pos(d, :)), max(pos(d, :))];
        %         end
        %         v_max = (dim_range(:, 2) - dim_range(:,1))/100
        %         [pos v] = shuffle_pos_v(dim_range, agent_count, v_max);
        %         x_pos_std = [];
        %         y_pos_std = [];
        %         % no_of_bins = ceil(no_of_bins/2)
        %     end 
        % end 
    end
    % States: 
    % iterations = i
    % best_pos
    % best_val
    % v_max
    % x_std = std(pos(1, :))
    % y_std = std(pos(2, :))
    % agent_count
    % mean_curr_std = mean(curr_std)

    
    % ackley_fn(best_pos')    
    % figure, plot((1:length(best_val_hist)), best_val_hist);
end
