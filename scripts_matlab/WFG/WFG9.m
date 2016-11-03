function [ obj ] =WFG9( m,k,z )
c=size(z,2);
n=size(z,1);
bu=2:2:2*c;
x=z./(ones(n,1)*bu);
A=0.98/49.98;
B=0.02;
C=50;
for i=1:c-1
    y=x(:,i+1:c);
    Y=sum(y,2)/size(y,2);
    for j=1:size(Y,1)
        if Y(j)<0.5
            u(j,1)=Y(j)*((C-B)*A)*2+B;
        else
            u(j,1)=(Y(j)-0.5)*(C-((C-B)*A+B))*2+(C-B)*A+B;
        end
    end
    v=A-(1-2*u).*abs(floor(0.5-u)+A);
    t1(:,i)=x(:,i).^(B+(C-B)*v);
end
t1(:,c)=x(:,c);

A=0.35;
B=0.001;
C=0.05;
for i=1:k
    t2(:,i)=1+(abs(t1(:,i)-A)-B).*(floor(t1(:,i)-A+B)*(1-C+(A-B)/B)/(A-B)+floor(A+B-t1(:,i))*(1-C+(1-A-B)/B)/(1-A-B)+1/B);
end
A=30;
B=95;
C=0.35;
for i=k+1:c
    t2(:,i)=(1+cos((4*A+2)*pi*(0.5-(abs(t1(:,i)-C))./(2*(floor(C-t1(:,i))+C))))+4*B*(((abs(t1(:,i)-C))./(2*(floor(C-t1(:,i))+C))).^2))/(B+2);
end

for i=1:m-1
    y=t2(:,(i-1)*k/(m-1)+1:i*k/(m-1));
    A=k/(m-1);
    for j=1:size(y,2)
        s(:,j)=y(:,j);
        for p=0:A-2
            s(:,j)=s(:,j)+abs(y(:,j)-y(:,1+mod(j+p,size(y,2))));
        end
    end
    t3(:,i)=sum(s,2)/(size(y,2)/A*ceil(A/2)*(1+2*A-2*ceil(A/2)));
end
y=t2(:,k+1:end);
A=c-k;
for j=1:size(y,2)
    s(:,j)=y(:,j);
    for p=0:A-2
        s(:,j)=s(:,j)+abs(y(:,j)-y(:,1+mod(j+p,size(y,2))));
    end
end
t3(:,m)=sum(s,2)/(size(y,2)/A*ceil(A/2)*(1+2*A-2*ceil(A/2)));
x=[];
for i=1:1
    x(:,i)=max(t3(:,m),ones(n,1)).*(t3(:,i)-0.5)+0.5;
end
for i=2:m-1
    x(:,i)=max(t3(:,m),ones(n,1)).*(t3(:,i)-0.5)+0.5;
end
x(:,m)=t3(:,m);

h(:,1)=prod(sin(0.5*pi*x(:,1:m-1)),2);
for i=2:m-1
    h(:,i)=prod(sin(0.5*pi*x(:,1:m-i)),2).*(cos(0.5*pi*x(:,m-i+1)));
end
h(:,m)=cos(0.5*pi*x(:,1));
s=2:2:2*m;
s=ones(n,1)*s;
obj=x(:,m)*ones(1,m)+s.*h;
end

