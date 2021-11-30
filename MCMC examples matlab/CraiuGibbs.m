function [ beta ] = CraiuGibbs(X,Y,T,u,R)
[N,P]=size(X);
beta0=zeros(1,P);
beta0=[-1.778, 4.374, 2.482];
psi0=zeros(1,N);
Un1=u(:,1:P);
Un2=u(:,P+1:P+N);
for t=1:T
betatilda= X'*X\(X'*psi0');
if isempty(R)
N=norminv(Un1(t,:));    
else
N=R(t,:).*(2*Un1(t,:)-1);
end
beta(t,:)= betatilda + chol(X'*X)'\N';
UU(t,:)=normcdf(-(X*beta(t,:)')')+Un2(t,:).*(1-normcdf(-(X*beta(t,:)')'));
psi(t,:)=(-1+2*Y').*((X*beta(t,:)')' + norminv(UU(t,:)));
beta0=beta(t,:);
psi0=psi(t,:);   
end