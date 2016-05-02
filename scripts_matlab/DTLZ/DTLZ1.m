function f = DTLZ1( M, X )
    f = zeros(1, M);
    k=5;
    xm = X(M:end);
    g = 100*(k+sum((xm-0.5).^2 - cos(20*pi*(xm-0.5))));
    f(1) = 0.5*prod(X(1:M-1))*(1+g);
    f(M) = 0.5*(1-X(1))*(1+g);
    for i = 2:M-1
        f(i) = 0.5*prod(X(1:M-i))*(1-X(M-i+1))*(1+g);
    end
end

