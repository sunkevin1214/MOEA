function [ obj ] =WFG6( m,k,z )
c=size(z,2);
n=size(z,1);
bu=2:2:2*c;
x=z./(ones(n,1)*bu);
t1(:,1:k)=x(:,1:k);
t1(:,k+1:c)=abs(x(:,k+1:c)-0.35)./abs(floor(0.35-x(:,k+1:c))+0.35);

for i=1:m-1
    y=t1(:,(i-1)*k/(m-1)+1:i*k/(m-1));
    A=k/(m-1);
    for j=1:size(y,2)
        s(:,j)=y(:,j);
        for p=0:A-2
            s(:,j)=s(:,j)+abs(y(:,j)-y(:,1+mod(j+p,size(y,2))));
        end
    end
    t2(:,i)=sum(s,2)/(size(y,2)/A*ceil(A/2)*(1+2*A-2*ceil(A/2)));
end
y=t1(:,k+1:end);
A=c-k;
for j=1:size(y,2)
    s(:,j)=y(:,j);
    for p=0:A-2
        s(:,j)=s(:,j)+abs(y(:,j)-y(:,1+mod(j+p,size(y,2))));
    end
end
t2(:,m)=sum(s,2)/(size(y,2)/A*ceil(A/2)*(1+2*A-2*ceil(A/2)));
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

