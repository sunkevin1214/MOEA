function f = DTLZ6(  M, X )
    f = zeros(1, M);
    xm = X(M:end);
    g = sum(xm.^(0.1));
    theta = 0.5*(1+2*g*X)/(1+g);
    theta(1) = X(1);
    theta(2) = X(2);
    f(1) = (1+g)*prod(cos(theta(1:M-1).*pi./2));
    f(M) = (1+g)*sin(theta(1)*pi/2);
    for i =2:M-1
        f(i) = (1+g)*prod(cos(theta(1:M-i).*pi./2))*sin(theta(M-i+1)*pi/2);
    end

end

