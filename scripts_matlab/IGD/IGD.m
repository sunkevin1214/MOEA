function rs = IGD(tf, approximate_pf)
    min_v = min(tf, [], 1);
    max_v = max(tf, [], 1);
    %norm_x = approximate_pf;
    norm_pf = normalization(tf, min_v, max_v);
    norm_apfx = normalization(approximate_pf, min_v, max_v);
    dist = pdist2(norm_pf, norm_apfx);
    min_dist = min(dist, [], 2);
    rs = sqrt(sum(min_dist.^2))/size(tf,1);
end