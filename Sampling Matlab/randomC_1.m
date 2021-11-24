function[U,V,A]=randomC_1(N,dim)
%Function for sampling from Circulant Variates C({1})  
%Input
%n=number of samples
%dim= dimension of the random vector
%Output
%A coordinate matrix
%V n samples from C({1}) random vector of dimension k
%U n samples from C({1}) random vector of dimension k 
% exchangeable version 
u=repmat(rand(N,1),1,dim);
v=rand(N,1);
%Build the coordinate matrix by circular permutations
A(1,:)=[0:(dim-1)]/(dim-1);
for dd=[1:dim-1]
A= [A;circshift(A(1,:),dd)]; 
end 
%Build the edge set
[iv jv]=find(sparse(tril(repmat(true,dim,dim),-1)));
diffij=((abs(iv-jv)<=1)|(abs(iv-jv)>=(dim-1)));
iv=iv(diffij);
jv=jv(diffij);
Ne=size(iv,1);
%Random selection of the edge
ijvec=floor(v*Ne)+1;
pp2=[iv(ijvec) jv(ijvec)];
v1=u;
% C({1})
V=[v1.*A(pp2(:,1),:)+ (1-v1).*A(pp2(:,2),:)];
% Random permutation of C({1})
U=Shuffle(U,2);
end