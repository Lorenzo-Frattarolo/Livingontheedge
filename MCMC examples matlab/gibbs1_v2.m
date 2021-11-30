function [ theta ,acc ] = gibbs1_v2(s,t,n,K,burn,u)
theta=NaN(K,n+2);
acc=zeros(K,1);
theta(1,:)=0.1*ones(1,n+2);
for k=2:K+burn
    for j=1:n
        theta(k,j)=icdf('gamma',u(k,j),theta(k-1,n+1)+s(j),1/(theta(k-1,n+2)+t(j)));   
    end
    z=0.8;
    [theta(k,n+1),acc(k,1)]= MH_V2(theta(k-1,n+1),theta(k,1:n),theta(k-1,n+2),n,z,u(k,n+1:n+2));
    theta(k,n+2)=icdf('gamma',u(k,n+3),n*theta(k,n+1)+0.1,1/(1+sum(theta(k,1:n))));
clc    
end
theta=theta(burn+1:end,:);
acc=acc(burn+1:end,:);
end


