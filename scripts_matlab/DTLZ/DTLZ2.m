function f = DTLZ2(  M, X )
    f = zeros(1, M);
    xm = X(M:end);
    g = sum((xm-0.5).^2);
    f(1) = (1+g)*prod(cos(X(1:M-1).*pi./2));
    f(M) = (1+g)*sin(X(1)*pi/2);
    for i =2:M-1
        f(i) = (1+g)*prod(cos(X(1:M-i).*pi./2))*sin(X(M-i+1)*pi/2);
    end
 
end

