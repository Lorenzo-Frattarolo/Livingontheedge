clc
clear all
%Computation of effective dimension
d=50;
avec=[0.1,1,10];
tauvec=[0.1,0.5,0.8,0.9,1];

for i=1:length(avec)
    for j=1:length(tauvec)
        a=avec(i);
        tau=tauvec(j);
        [dt(i,j),ds(i,j)]=effectivedimwangsloan(d,0.99,a,tau);        
    end
end