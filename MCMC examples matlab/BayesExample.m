function[tablealpha,tablebeta,tablebetaprob,HP,BP]=BayesExample(K)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Metropolis within Gibbs Hierarchical Poisson Gelfand and
%Smith (1990)
%Data%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
s=[ 5 1 5 14 3 19 1 1 4 22];
t=[94.320 15.720 62.880 125.760 5.240 31.440 1.048 1.048 2.096 10.480];
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
n=10; %number of observations 
burn=0;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
uv2=rand(K+burn,n+3);
tic
[HP.varalpha1,HP.varbeta1,HP.malpha1,HP.mbeta1 ] = AsymvarianceHyPois(s,t,n,uv2);
HP.tsimpl1=toc;
for d=2:20
clear ud udp udilh 
for j=1:n+3
[udp(:,j,:)]=ILHC1RBS(max(floor(K/d),1),d,0);
[ud(:,j,:) ]=ILHC1RBS(max(floor(K/d),1),d,1);
[udilh(:,j,:)]=ILHFaster(max(floor(K/d),1),d,3);
end
tic
[varalpha(d-1),varbeta(d-1),ma,mb] = AsymvarianceHyPois(s,t,n,ud);
HP.malpha(:,d-1).ma=ma;
HP.mbeta(:,d-1).mb=mb;
HP.tsimpl(d-1)=toc;
tic
[varalphap(d-1),varbetap(d-1),ma,mb] = AsymvarianceHyPois(s,t,n,udp);
HP.malphap(:,d-1).ma=ma;
HP.mbetap(:,d-1).mb=mb;
HP.tsimplp(d-1)=toc;
tic
[varalphailh(d-1),varbetailh(d-1),ma,mb] = AsymvarianceHyPois(s,t,n,udilh);
HP.malphailh(:,d-1).ma=ma;
HP.mbetailh(:,d-1).mb=mb;
HP.tilh(d-1)=toc;
end
tablealpha=[varalpha'./HP.varalpha1,varalphap'./HP.varalpha1,varalphailh'./HP.varalpha1];
tablebeta=[varbeta'./HP.varbeta1,varbetap'./HP.varbeta1,varbetailh'./HP.varbeta1];
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Bayesian inference on Probit van Dyk and Meng (2001)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
load lupus.mat
Y=num(:,2);
X=num(:,3:end);
[N,P]=size(X);
T=K;
u(:,1:P)=rand(T,P);
u(:,P+1:P+N)=rand(T,N);
tic
[BP.varbetaprob1,BP.mbetaprob1 ] = AsymvarianceBprob(X,Y,u,[]);
BP.t1prob(d-1)=toc;
for d=2:20
clear ud udp udilh Ra
for j=1:N+P
[udp(:,j,:)]=ILHC1RBS(max(floor(K/d),1),d,0);
[ud(:,j,:) ]=ILHC1RBS(max(floor(K/d),1),d,1);
[udilh(:,j,:)]=ILHFaster(max(floor(K/d),1),d,3);
end
tic
[varbetaprob(d-1,:),mb] = AsymvarianceBprob(X,Y,ud,[]);
BP.mbetaprob(d-1).mb=mb;
BP.tsimplprob(d-1)=toc;
tic
[varbetapprob(d-1,:),mb] = AsymvarianceBprob(X,Y,udp,[]);
BP.mbetapprob(d-1).mb=mb;
BP.tsimplpprob(d-1)=toc;
tic
[varbetailhprob(d-1,:),mb] = AsymvarianceBprob(X,Y,udilh,[]);
BP.mbetailhprob(d-1).mb=mb;
BP.tilhprob(d-1)=toc;
end
for i=1:P
tablebetaprob(i).table=[varbetaprob(:,i)./BP.varbetaprob1(:,i),varbetapprob(:,i)./BP.varbetaprob1(:,i),varbetailhprob(:,i)./BP.varbetaprob1(:,i)];
end    
end
