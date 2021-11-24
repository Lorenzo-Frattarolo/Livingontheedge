function[U]=ILHFaster(n,k,T)
%Function for sampling from Iterated Latin Hypercube 
%Input
%n=number of samples
%k= dimension of the random vector
%T= Latin Hypercube Iterations ( 0 no iterations)
%Output
%U n samples from ILH(T) random vector of dimension k 
U=rand(n,k);
K=repmat(1:k,n,1);
t=0;
while t<T
t=t+1;    
U= 1/k*(Shuffle(K,2)-1 +U);
end
end