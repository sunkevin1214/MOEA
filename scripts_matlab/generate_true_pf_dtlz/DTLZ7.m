function [f, obj] = DTLZ7(  M, X )
    f = zeros(1, M);
    xm = X(M:end);
    g = 1+(9/numel(xm))*sum(xm);
    
    for i =1:M-1
        f(i) = X(i);
    end
    h = M - sum((f(1:M-1)./(1+g)).*(1+sin(3*pi*f(1:M-1))));
    f(M) = (1+g)*h;
    
    x = X;
  
    xg=x(3:end);
     gx=1+(9/(numel(xm)))*sum(xg);  
     obj(1)=x(1);
     obj(2)=x(2);
     hf=3-(obj(1)/(1+gx))*(1+sin(3*pi*obj(1)))-(obj(2)/(1+gx))*(1+sin(3*pi*obj(2)));
     obj(3)=(1+gx)*hf; 

end

