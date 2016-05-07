function dist = perpendicular(vectors, s)
%% compute the perpendocular distance of s to the vector in vectors
%% s, 1 by n, vectors, m by n. n denotes the dimension and m denotes the number of vector
% for vector v in vectors, the perpendicular distance is calculated by:
% ||s - vsv'/(vv')||
norm_dist = sum(vectors.^2, 2);
coff = s*vectors';
coff = coff';
coff = coff./norm_dist;
project_v = vectors.*repmat(coff, 1, numel(s));
dist = sqrt(sum((repmat(s, size(vectors, 1), 1) - project_v).^2, 2));
end