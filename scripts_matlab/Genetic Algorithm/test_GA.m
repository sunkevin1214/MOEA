function test_GA() 
    % dejong 1
%     fun_handle = @(M,x)f1(x);
%     l_limit = -5.12*ones(1,2);
%     u_limit = 5.12*ones(1,2);
%     solution = GA(fun_handle, l_limit, u_limit);
    % dejong 2
%     fun_handle = @(M, x)f2(x);
%     l_limit = -2.048*ones(1,2);
%     u_limit = 2.048*ones(1,2);
%     solution = GA(fun_handle, l_limit, u_limit);
    % Schwefel's Function
    fun_handle = @(M, x)f3(x);
    l_limit = -500*ones(1,5);
    u_limit = 500*ones(1,5);
    solution = GA(fun_handle, l_limit, u_limit);
    
    solution
end

function y = f1(x)
% dejong1, x1, x2 \in [-5.12, 5.12];
    y = sum(x.^2);
end

function y = f2(x)
%dejong2, x1, x2 \in [-2.048, 2.048]
    y = 100*(x(1).^2-x(2)).^2 + (1-x(1)).^2;
end

function y = f3(x)
%Schwefel's Function, dimension is set to 5; x_i \in [-500, 500];
    y = 418.9829*numel(x)-sum(x.*sin(sqrt(abs(x))));
end