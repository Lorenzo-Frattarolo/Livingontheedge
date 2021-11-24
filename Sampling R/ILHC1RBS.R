ILHC1RBS <- function(n,d,T)
{
  #Function for sampling from Circulant Variates C({1}) 
  #using the Random Balanced Sampling (RBS) equivalence
  #and Circulant variates with Latin Hypercube (LH) Iterations  
  #Input
  #n=number of samples
  #d= dimension of the random vector
  #T= Latin Hypercube Iterations ( 0 no iterations)
  #Output
  #V n samples from C({1}) random vector of dimension d
  #U n samples from C({1}) random vector of dimension d 
  #with T LH iterations 
  
  
  D<-t(array(rep(1:d,n),dim=c(d,n)))
  U1<-runif(n, min = 0, max = 1)
  U<-cbind(U1,(D[,2:ncol(D)]-1)/(d-1)-array(rep(U1,n),dim=c(n,d-1))/(d-1))
  V<-t(apply(U,1,sample))
  tt<-0
  while (tt<T)
  {T<-
    tt<-tt+1
    V<-1/d*(t(apply(D,1,sample))-1+V)
  }
  V
}