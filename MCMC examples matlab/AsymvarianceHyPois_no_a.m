function [varalpha,varbeta,malpha,mbeta ] = AsymvarianceHyPois_no_a(s,t,n,u)
D=size(u,3);
K=size(u,1);
for d=1:D
 theta(d,:,:)=gibbs1_v2_no_a(s,t,n,K,0,squeeze(u(:,:,d))); 
end
bn=floor(sqrt(K));
malpha= mean(theta(:,:,n+1),1)';
mbeta= mean(theta(:,:,n+2),1)';
[varalpha] = SAsymVarTH(malpha,bn);
[varbeta] = SAsymVarTH(mbeta,bn);
end

