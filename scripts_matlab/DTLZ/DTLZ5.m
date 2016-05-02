function f = DTLZ5(  M, X )
    f = zeros(1, M);
    xm = X(M:end);
    g = sum((xm-0.5).^2);
    theta = (pi/(4*(1+g)))*(1+2*g*X);
    theta(1) = X(1);
    f(1) = (1+g)*prod(cos(theta(1:M-1).*pi.*0.5));
    f(M) = (1+g)*sin(theta(1)*pi*0.5);
    for i =2:M-1
        f(i) = (1+g)*prod(cos(theta(1:M-i).*pi./2))*sin(theta(M-i+1)*pi/2);
    end

end

