function create_pf( )
objs = [10, 15];
divs = [6,6;5,4]; % two layers for generating reference weights
% objs = [8];
% divs = [9];
f = @dtlz7;
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

% for DTLZ5,6,7, we do not know the exact regularity of the pareto front,
% so a random method is utilized for generate the true pareto front for IGD
% calculating.
function dtlz5(div, obj)
    count = 0;
    for i = 1:numel(div)
        count = count + nchoosek(div(i)+obj-1, div(i));
    end
    ps = rand(count, obj+10-1);
    ps(:, obj:end) = 0.5;
    pf = zeros(count, obj);
    for i = 1:count
        pf(i,:) = DTLZ5(obj, ps(i,:));
    end
    file_name = sprintf('dtlz5_tf_%dobjs.txt', obj);
    save(file_name, 'pf', '-ascii');
end

function dtlz6(div, obj)
   count = 0;
    for i = 1:numel(div)
        count = count + nchoosek(div(i)+obj-1, div(i));
    end
    ps = rand(count, obj+10-1);
    ps(:, obj:end) = 0.0;
    pf = zeros(count, obj);
    for i = 1:count
        pf(i,:) = DTLZ6(obj, ps(i,:));
    end
    file_name = sprintf('dtlz6_tf_%dobjs.txt', obj);
    save(file_name, 'pf', '-ascii');
end

function dtlz7(div, obj)
    count = 0;
    for i = 1:numel(div)
        count = count + nchoosek(div(i)+obj-1, div(i));
    end
    ps = rand(count, obj+20-1);
    ps(:, obj:end) = 0.0;
    pf = zeros(count, obj);
    for i = 1:count
        pf(i,:) = DTLZ7(obj, ps(i,:));
    end
    file_name = sprintf('dtlz7_tf_%dobjs.txt', obj);
    save(file_name, 'pf', '-ascii');
end