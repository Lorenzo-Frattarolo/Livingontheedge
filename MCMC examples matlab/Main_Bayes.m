clc
clear all
close all
rng(1)
h = waitbar(0,'wait');
K=5000;
niter=1000;
addpath(genpath('..\'))
for rep =1:niter
    
%Hierarchical Poisson with antithetic acceptance and Bayesian Probit    
[tablealpha(rep,:,:),tablebeta(rep,:,:),tablebetaprob(rep,:),HP(rep),BP(rep)]=BayesExample(K);
save BayesTables20-5000-1000.mat


%Hierarchical Poisson without antithetic acceptance    
[tablealpha_noa(rep,:,:),tablebeta_noa(rep,:,:),~,HP_noa(rep),~]=BayesExample_no_acceptance(K);
save BayesTables20-5000-1000_no_a.mat

waitbar(rep/niter,h)
end

