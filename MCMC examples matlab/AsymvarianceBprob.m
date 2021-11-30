function [varbeta,mbeta ] = AsymvarianceBprob(X,Y,u,R)
D=size(u,3);
T=size(u,1);
for d=1:D
 beta(d,:,:)=CraiuGibbs(X,Y,T,squeeze(u(:,:,d)),R); 
end
bn=floor(sqrt(T));
mbeta= squeeze(mean(beta,1));
for i=1:size(X,2)
[varbeta(i)] = SAsymVarTH(mbeta(:,i),bn);
end

