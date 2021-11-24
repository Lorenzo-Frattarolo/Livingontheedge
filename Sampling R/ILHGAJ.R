ILHGAJ <- function(n,d,b,T)
{
  #Function for sampling from b-based Arvidsen and Johnson (AJ) 
  #random vector and b-based Arvidsen and Johnson with 
  #Latin Hypercube (LH) Iterations 
  #Input
  #n=number of samples
  #d= dimension of the random vector
  #b=base
  #T= Latin Hypercube Iterations ( 0 no iterations)
  #Output
  #V samples from AJ random vector of dimension k and base b
  #with T LH iterations 

  
  D<-t(array(rep(1:d,n),dim=c(d,n)))
  U<-array(0,dim=c(d,n))
  U[1,]<-runif(n, min = 0, max = 1)
  
  for(i in 2:d-1){
  a<-b^(i-2)*U[1,]+1/b
  U[i,]<-a-floor(a)
  }
  a<-b^(d-2)*U[1,]
  U[d,]<-1-(a-floor(a))
  U<-t(U)
  V<-t(apply(U,1,sample))
  tt<-0
  while (tt<T)
  {T<-
    tt<-tt+1
    V<-1/d*(t(apply(D,1,sample))-1+V)
  }
  V
}