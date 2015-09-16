function pso_print_result(val, pos)
    dim = length(pos);
    % format 
    format_str = '    %1.6f : [';
    for i=1:dim
        format_str = strcat(format_str, '%11.6f');
    end
    format_str = strcat(format_str, '   ]\n');
    fprintf(format_str, val, pos);
end
