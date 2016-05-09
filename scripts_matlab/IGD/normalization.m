function [ norm_x ] = normalization( x, min_x, max_x )
% x是一个矩阵，每一行代表一个样本，把x的每一列都归一化到min_v,max_v对应的区间内
% 按照jmetal的实现，全部归一化到[0,1]之间，但是approximate pareto front的上下区间来自true pareto
% front
assert(size(x, 2)==size(min_x, 2));
assert(size(min_x, 2)==size(max_x, 2));
dis_min_max = max_x - min_x;
x = bsxfun(@minus, x, min_x);
x = bsxfun(@rdivide, x, dis_min_max);
x(:, find(dis_min_max<1e-9)) = 0;
norm_x = x;
end

