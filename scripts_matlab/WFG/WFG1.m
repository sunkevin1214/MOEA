function [ obj ] =WFG1( m,k,z )
c=size(z,2);
n=size(z,1);
bu=2:2:2*c;
x=z./(ones(n,1)*bu);
t1(:,1:k)=x(:,1:k);
t1(:,k+1:c)=abs(x(:,k+1:c)-0.35)./abs(floor(0.35-x(:,k+1:c))+0.35);
t2(:,1:k)=t1(:,1:k);
A=0.8;
B=0.75;
C=0.85;
for i=k+1:c
    t2(:,i)=A+min(zeros(n,1),floor(t1(:,i)-B)).*(A*(B-t1(:,i))/B)-min(zeros(n,1),floor(C-t1(:,i))).*((1-A)*(t1(:,i)-C)/(1-C));
end
a=0.02;
for i=1:c
    t3(:,i)=t2(:,i).^a;
end
for i=1:m-1
    w=2*(i-1)*k/(m-1)+1:2:2*i*k/(m-1);
    y=t3(:,(i-1)*k/(m-1)+1:i*k/(m-1));
    W=repmat(w,n,1);
    t4(:,i)=sum(y.*W,2)/sum(w,2);
end
w=2*(k+1):2:2*c;
y=t3(:,k+1:end);
W=repmat(w,n,1);
t4(:,m)=sum(y.*W,2)/sum(w,2);
x=[];
for i=1:1
    x(:,i)=max(t4(:,m),ones(n,1)).*(t4(:,i)-0.5)+0.5;
end
for i=2:m-1
    x(:,i)=max(t4(:,m),ones(n,1)).*(t4(:,i)-0.5)+0.5;
end
x(:,m)=t4(:,m);

A=5;
a=1;

h(:,1)=prod(1-cos(0.5*pi*x(:,1:m-1)),2);
for i=2:m-1
    h(:,i)=prod(1-cos(0.5*pi*x(:,1:m-i)),2).*(1-sin(0.5*pi*x(:,m-i+1)));
end
h(:,m)=(1-x(:,1)-cos(2*A*pi*x(:,1)+0.5*pi)/(2*A*pi)).^a;
s=2:2:2*m;
s=ones(n,1)*s;
obj=x(:,m)*ones(1,m)+s.*h;
end

