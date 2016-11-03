function [ obj ] =WFG2( m,k,z )
c=size(z,2);
n=size(z,1);
bu=2:2:2*c;
x=z./(ones(n,1)*bu);
t1(:,1:k)=x(:,1:k);
t1(:,k+1:c)=abs(x(:,k+1:c)-0.35)./abs(floor(0.35-x(:,k+1:c))+0.35);
t2(:,1:k)=t1(:,1:k);
for i=k+1:k+(c-k)/2
    y=t1(:,k+(i-k)*2-1:k+(i-k)*2);
    t2(:,i)=(y(:,1)+y(:,2)+2*abs(y(:,1)-y(:,2)))/3;
end
for i=1:m-1
    y=t2(:,(i-1)*k/(m-1)+1:i*k/(m-1));
    t3(:,i)=sum(y,2)/size(y,2);
end
y=t2(:,k+1:end);
t3(:,m)=sum(y,2)/size(y,2);
x=[];
for i=1:1
    x(:,i)=max(t3(:,m),ones(n,1)).*(t3(:,i)-0.5)+0.5;
end
for i=2:m-1
    x(:,i)=max(t3(:,m),ones(n,1)).*(t3(:,i)-0.5)+0.5;
end
x(:,m)=t3(:,m);
A=5;
a=1;
b=1;
h(:,1)=prod(1-cos(0.5*pi*x(:,1:m-1)),2);
for i=2:m-1
    h(:,i)=prod(1-cos(0.5*pi*x(:,1:m-i)),2).*(1-sin(0.5*pi*x(:,m-i+1)));
end
h(:,m)=1-(x(:,1).^a).*(cos(A*pi*(x(:,1).^b)).^2);
s=2:2:2*m;
s=ones(n,1)*s;
obj=x(:,m)*ones(1,m)+s.*h;
end

