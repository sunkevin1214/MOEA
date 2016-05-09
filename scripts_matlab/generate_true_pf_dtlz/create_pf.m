function create_pf( )
%objs = [10, 15];
%divs = [6,6;5,4]; % two layers for generating reference weights
objs = [8];
divs = [9];
f = @dtlz1;
for i = 1:numel(objs)
    f(divs(i,:), objs(i));
end


end

function dtlz1(div, obj)
    pf = uniform_sample(obj, div);
    pf = pf./2;
    file_name = sprintf('dtlz1_tf_%dobjs.txt', obj);
    save(file_name, 'pf', '-ascii');
end

function dtlz2(div, obj)
    pf = uniform_sample(obj, div);
    pf = bsxfun(@rdivide, pf, sqrt(sum(pf.^2, 2)));
    file_name = sprintf('dtlz2_tf_%dobjs.txt', obj);
    save(file_name, 'pf', '-ascii');
end

function dtlz3(div, obj)
    pf = uniform_sample(obj, div);
    pf = bsxfun(@rdivide, pf, sqrt(sum(pf.^2, 2)));
    file_name = sprintf('dtlz3_tf_%dobjs.txt', obj);
    save(file_name, 'pf', '-ascii');
end

function dtlz4(div, obj)
    pf = uniform_sample(obj, div);
    pf = bsxfun(@rdivide, pf, sqrt(sum(pf.^2, 2)));
    file_name = sprintf('dtlz4_tf_%dobjs.txt', obj);
    save(file_name, 'pf', '-ascii');
end

function dtlz5(div, obj)
    pf = uniform_sample(obj, div);
    pf = bsxfun(@rdivide, pf, sqrt(sum(pf.^2, 2)));
    file_name = sprintf('dtlz5_tf_%dobjs.txt', obj);
    save(file_name, 'pf', '-ascii');
end

function dtlz6(div, obj)
    pf = uniform_sample(obj, div);
    pf = bsxfun(@rdivide, pf, sqrt(sum(pf.^2, 2)));
    file_name = sprintf('dtlz6_tf_%dobjs.txt', obj);
    save(file_name, 'pf', '-ascii');
end

function dtlz7(div, obj)
    % for dtlz, the samples are generated by ps
    % minimum = 5000; for 10 and 15, the divs should be 7, and 5,
    % respectively.
    div = -1;
    if obj == 10
        div = 7;
    end
    if obj == 15;
        div = 5;
    end
    k = 20;
    xDim = k + obj - 1;
    part_ps = uniform_sample(obj-1, div);
    ps = zeros(size(part_ps, 1), xDim);
    ps(:, 1:obj-1) = part_ps;
    pf = zeros(size(ps, 1), obj);
    for j = 1:size(pf, 1)
        pf(j, :) = DTLZ7(obj, ps(j, :));
    end
    file_name = sprintf('dtlz7_tf_%dobjs.txt', obj);
    save(file_name, 'pf', '-ascii');
end