function uniform_generate(p, objs, left, total, element)
%% this function are used to uniformly generate samples in the hyper-plane with intercept in each coordinate with 1.
    global points;
    if element == objs - 1
        p(element+1) = left/total;
        points = [points; p];
    else
        for i=0:left
            p(element+1) = i/total;
            uniform_generate( p, objs, left-i, total, element+1);
        end
    end
end