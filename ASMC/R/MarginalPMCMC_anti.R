###############################################################################################################################################

# RANDOM WALK PARTICLE MARGINAL METROPOLIS HASTINGS ALGORITHM

#parameters:

#y=(y_0,...,Y_{T-1}): dy*T vector of data
#dx		    : dimensions of of the hidden process
#m		    : length of the Markov chain
#theta0	 	    : starting point of the Markov chain
#prior		    : density function of the prior distribution
#parPrior	    : parameters of "prior"
#N		    : number of particles for the filter
#qmc		    : if TRUE, Owens's scrambled Sobol' sequence is used as imput (forward and backward step)
#		      if FALSE, SMC is used (forward and backward step)
#parFilter	    : functions that puts "theta0" in the right format to be used in the filter
#filter		    : filter algorithm

################################################################################################################################################

library("mnormt")

Marginal_PMCMC_anti=function(y, dx, m, c, theta0, prior, parPrior, N, qmc,  parFilter, filter)
{
	n=nrow(y)
	dy=ncol(y)
	T=nrow(y)
	np=length(theta0)
	theta=matrix(0,np,m)
	

	theta[,1]=theta0
	d=0
 il=0
	work=parFilter(theta[,1],dx,dy)
	p0=prior(theta[,1], dx, dy, parPrior)+filter(y, dx, work, N,il, qmc)$L[T]
	p1=0

	for(i in 2:m)
	#print(i/m)
	{
		theta1=theta[,(i-1)]+rmnorm(1,rep(0,np),c)
		
		p1=prior(theta1, dx, dy, parPrior)

		if(p1==-Inf)
		{
			theta[,i]=theta[,(i-1)]
		}else
		{
			work=parFilter(theta1,dx,dy)
			p1=p1+filter(y, dx, work, N,il, qmc)$L[T]

			if(log(runif(1))>p1-p0 | p1=="NaN")
			{

				theta[,i]=theta[,(i-1)]

			}else
			{
			  #print('Hello')
				theta[,i]=theta1
				p0=p1
				d=d+1
			}	
		}	
	}
	return(list(Y=theta, P=d/m))
}


























