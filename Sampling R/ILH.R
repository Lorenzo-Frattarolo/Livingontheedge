ILH <- function(n,d,T)
{
  #Function for sampling from Iterated Latin Hypercube  
  #Input
  #n=number of samples
  #d= dimension of the random vector
  #T= Latin Hypercube Iterations ( 0 no iterations)
  #Output
  #V n samples from ILH(T) random vector of dimension

  
  D<-t(array(rep(1:d,n),dim=c(d,n)))
  V<-array(runif(n*d, min = 0, max = 1),dim=c(n,d))
  tt<-0
  while (tt<T)
  {T<-
    tt<-tt+1
    V<-1/d*(t(apply(D,1,sample))-1+V)
  }
  V
}