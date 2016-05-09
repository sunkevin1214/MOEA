function [ norm_x ] = normalization( x, min_x, max_x )
% x��һ������ÿһ�д���һ����������x��ÿһ�ж���һ����min_v,max_v��Ӧ��������
% ����jmetal��ʵ�֣�ȫ����һ����[0,1]֮�䣬����approximate pareto front��������������true pareto
% front
assert(size(x, 2)==size(min_x, 2));
assert(size(min_x, 2)==size(max_x, 2));
dis_min_max = max_x - min_x;
x = bsxfun(@minus, x, min_x);
x = bsxfun(@rdivide, x, dis_min_max);
x(:, find(dis_min_max<1e-9)) = 0;
norm_x = x;
end

