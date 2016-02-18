function data = uniform_sample(objs, divs)
    global points;
    points = [];
    p = zeros(1, objs);
    g(p, objs, divs, divs, 0);
    data = points;
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