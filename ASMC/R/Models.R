########################################################

library("mnormt")

## Univariate non linear and non stationnary model #############################################################################################

NL_sim=function(T,theta,x0)
{
	x=matrix(0,T)
	y=matrix(0,T)
	y[1]=rnorm(1,x0^2/theta[6],1)
	x[1]=x0
	for(k in 2:T)
	{
		x[k]=theta[1]*x[k-1]+theta[2]*x[k-1]/(1+x[k-1]^2)+theta[3]*cos(theta[4]*(k-1))+rnorm(1,0,theta[5])
		y[k]=rnorm(1,x[k]^2/theta[6],1)
	}
	return(list(Y=y,X=x))
}



## Multivariate SV model ##############################################################################

SVM_sim=function(T,mu, Phi, Psi, C, x0)
{
	dx=ncol(Phi)
	x=matrix(0,T,dx)
	y=matrix(0,T,dx)
	
	e=matrix(rmnorm(1,rep(0,2*dx),C))
	y[1,]=exp(0.5*x0)*e[1:dx]
	x[1,]=x0
	for(k in 2:T)
	{
		e=matrix(rmnorm(1,rep(0,2*dx),C))
		x[k,]=mu+Phi%*%(x[k-1,]-mu)+sqrt(Psi)%*%e[(dx+1):(2*dx)]
		y[k,]=exp(0.5*x[k,])*e[1:dx]
		xx=x[k,]
	}
	return(list(Y=y,X=x))
}



## Neuro decoding model ##############################################################################

Neuro_sim=function(T,alpha,beta,delta,Phi,Sx,x0)
{
	dx=ncol(Phi)
	dy=length(alpha)
	x=matrix(0,T,dx)
	y=matrix(0,T,dy)
	
	x[1,]=x0
	lambda=(log(delta)+alpha+beta%*%x[1,])
	for(i in 1:dy)
	{
		y[1,i]=rpois(1,c(exp(lambda[i])))
	}
	for(k in 2:T)
	{
		x[k,]=Phi%*%x[k-1,]+matrix(c(rmnorm(1,rep(0,dx/2),Sx[1:(dx/2),1:(dx/2)]),rep(0,(dx/2))))
		
		lambda=(log(delta)+alpha+beta%*%x[k,])
		for(i in 1:dy)
		{
			y[k,i]=rpois(1,c(exp(lambda[i])))
		}
	}
	return(list(Y=y,X=x))
}



