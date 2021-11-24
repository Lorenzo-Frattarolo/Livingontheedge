function[U, V]=ILHGAJ(N,D,b,T)
%Function for sampling from b-based Arvidsen and Johnson (AJ) 
%random vector and b-based Arvidsen and Johnson with 
%Latin Hypercube (LH) Iterations  
%Input
%n=number of samples
%D= dimension of the random vector
%b= base 
%T= Latin Hypercube Iterations ( 0 no iterations)
%Output
%V n samples from AJ random vector of dimension k and base b
%U n samples from AJ random vector of dimension k and base b
%with T LH iterations 
U(1,:)=rand(N,1);
for i=2:D-1
a=b^(i-2)*U(1,:)+1/b;
U(i,:)=a-floor(a);
end
a=b^(D-2)*U(1,:);
U(D,:)=1-(a-floor(a));
U=U';
U=Shuffle(U,2);
V=U;
t=0;
K=repmat([1:D],N,1);
while t<T
t=t+1;    
U= 1/D*(Shuffle(K,2)-1 +U);
end
end