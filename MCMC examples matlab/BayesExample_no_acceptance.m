function[tablealpha,tablebeta,tablebetaprob,HP,BP]=BayesExample_no_acceptance(K)
% Metropolis within Gibbs Hierarchical Poisson Gelfand and
% Smith (1990) without antithetic acceptance 
%Data%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
s=[ 5 1 5 14 3 19 1 1 4 22];
t=[94.320 15.720 62.880 125.760 5.240 31.440 1.048 1.048 2.096 10.480];
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
n=10; %number of observations
burn=0;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Standard MC
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
uv2=rand(K+burn,n+2);
tic
[HP.varalpha1,HP.varbeta1,HP.malpha1,HP.mbeta1 ] = AsymvarianceHyPois_no_a(s,t,n,uv2);
HP.tsimpl1=toc;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% C({1}) , LHC({1}) ,ILH(3)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
for d=2:20
clear ud udp udilh 
for j=1:n+2
[udp(:,j,:)]=ILHC1RBS(max(floor(K/d),1),d,0);
[ud(:,j,:) ]=ILHC1RBS(max(floor(K/d),1),d,1);
[udilh(:,j,:)]=ILHFaster(max(floor(K/d),1),d,3);
end
tic
[varalpha(d-1),varbeta(d-1),ma,mb] = AsymvarianceHyPois_no_a(s,t,n,ud);
HP.malpha(:,d-1).ma=ma;
HP.mbeta(:,d-1).mb=mb;
HP.tsimpl(d-1)=toc;
tic
[varalphap(d-1),varbetap(d-1),ma,mb] = AsymvarianceHyPois_no_a(s,t,n,udp);
HP.malphap(:,d-1).ma=ma;
HP.mbetap(:,d-1).mb=mb;
HP.tsimplp(d-1)=toc;
tic
[varalphailh(d-1),varbetailh(d-1),ma,mb] = AsymvarianceHyPois_no_a(s,t,n,udilh);
HP.malphailh(:,d-1).ma=ma;
HP.mbetailh(:,d-1).mb=mb;
HP.tilh(d-1)=toc;
end
%Write table with results
tablealpha=[varalpha'./HP.varalpha1,varalphap'./HP.varalpha1,varalphailh'./HP.varalpha1];
tablebeta=[varbeta'./HP.varbeta1,varbetap'./HP.varbeta1,varbetailh'./HP.varbeta1];
tablebetaprob=[];
BP=[];
end
