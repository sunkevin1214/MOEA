function [ obj ] =WFG5( m,k,z )
c=size(z,2);
n=size(z,1);
bu=2:2:2*c;
x=z./(ones(n,1)*bu);
A=0.35;
B=0.001;
C=0.05;

for i=1:c
    t1(:,i)=1+(abs(x(:,i)-A)-B).*(floor(x(:,i)-A+B)*(1-C+(A-B)/B)/(A-B)+floor(A+B-x(:,i))*(1-C+(1-A-B)/B)/(1-A-B)+1/B);
end
for i=1:m-1
    y=t1(:,(i-1)*k/(m-1)+1:i*k/(m-1));
    t2(:,i)=sum(y,2)/size(y,2);
end
y=t1(:,k+1:end);
t2(:,m)=sum(y,2)/size(y,2);
x=[];
for i=1:1
    x(:,i)=max(t2(:,m),ones(n,1)).*(t2(:,i)-0.5)+0.5;
end
for i=2:m-1
    x(:,i)=max(t2(:,m),ones(n,1)).*(t2(:,i)-0.5)+0.5;
end
x(:,m)=t2(:,m);

h(:,1)=prod(sin(0.5*pi*x(:,1:m-1)),2);
for i=2:m-1
    h(:,i)=prod(sin(0.5*pi*x(:,1:m-i)),2).*(cos(0.5*pi*x(:,m-i+1)));
end
h(:,m)=cos(0.5*pi*x(:,1));
s=2:2:2*m;
s=ones(n,1)*s;
obj=x(:,m)*ones(1,m)+s.*h;
end

