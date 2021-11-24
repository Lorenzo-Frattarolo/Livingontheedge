function[U,V]=ILHC1RBS(n,k,T)
%Function for sampling from Circulant Variates C({1}) 
%using the Random Balanced Sampling (RBS) equivalence
%and Circulant variates with Latin Hypercube (LH) Iterations  
%Input
%n=number of samples
%k= dimension of the random vector
%T= Latin Hypercube Iterations ( 0 no iterations)
%Output
%V n samples from C({1}) random vector of dimension k
%U n samples from C({1}) random vector of dimension k 
%with T LH iterations 
K=repmat([1:k],n,1);
U1=rand(n,1);
U=[U1,(K(:,2:end)-1)/(k-1)- repmat(U1,1,k-1)/(k-1)];
U=Shuffle(U,2);
V=U;
t=0;
while t<T
t=t+1;    
U= 1/k*(Shuffle(K,2)-1 +U);
end
end