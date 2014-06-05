function [bins bin_tags] = bin_count(data, range, bin_size)
    bin_tags = (range(1):(range(2)-bin_size));
    len = length(bin_tags);
    bins = zeros(1, len);
    for i=1:len
        index = int32(floor(data(i) - range(1))) + 1;
        if index < 1,   index = 1; end 
        if index > len, index = len; end 
        bins(index) = bins(index) + 1;
    end 
end
