function data = uniform_sample(objs, divs)
    global points;
    points = [];
    p = zeros(1, objs);
    g(p, objs, divs(1), divs(1), 0);
    data = points;
    % the second layer
    if numel(divs) == 2
         points = [];
         g(p, objs, divs(2), divs(2), 0);
         sec_data = points;
         center = 1.0/objs;
         sec_data = (sec_data + center)/2;
         data = [data; sec_data];
    end
end

function g(p, objs, left, total, element)
%% this function are used to uniformly generate samples in the hyper-plane with intercept in each coordinate with 1.
    global points;
    if element == objs - 1
        p(element+1) = left/total;
        points = [points; p];
    else
        for i=0:left
            p(element+1) = i/total;
            g( p, objs, left-i, total, element+1);
        end
    end
end