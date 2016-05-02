function f = DTLZ4(  M, X )
    f = zeros(1, M);
    xm = X(M:end);
    g = sum((xm-0.5).^2);
    f(1) = (1+g)*prod(cos(X(1:M-1).^100.*pi./2));
    f(M) = (1+g)*sin(X(1)^100*pi/2);
    for i =2:M-1
        f(i) = (1+g)*prod(cos(X(1:M-i).^100.*pi./2))*sin(X(M-i+1).^100*pi/2);
    end

end

