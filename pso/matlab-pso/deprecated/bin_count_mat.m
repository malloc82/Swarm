function [bins bin_tags] = bin_count_mat(data, ranges, no_of_bins)
    steps = (ranges(:, 2) - ranges(:, 1))/no_of_bins;
    [row, col] = size(data);

    bins     = zeros(row, no_of_bins);
    bin_tags = zeros(row, no_of_bins);
    
    for r=1:row
        tags = (ranges(r, 1):steps(r):ranges(r, 2));
        bin_tags(r, :) = tags(1:end-1);
    end 
    
    for r=1:row
        for c=1:col
            index = int32(floor((data(r, c) - ranges(r, 1)) / steps(r))) + 1;
            if index < 1,   index = 1; end 
            if index > no_of_bins, index = no_of_bins; end 
            bins(r, index) = bins(r, index) + 1;
        end
    end
end