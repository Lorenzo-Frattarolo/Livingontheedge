###############################################################
# 
# #MULTIVARIATE STOCHASTIC VOLATILITY MODEL
# 
# ###############################################################
#

rm(list=ls())

dyn.load("../../lib/SV_ASQMC.so")	

source("../../src/Models/SV_Model/ASQMC_SV.R")

source("../Models.R")

source("../MarginalPMCMC_anti.R") 

library("coda")				#used to compute ESS in PMMH-SQMC

subDir<-"SAMC_PCMC"
wd<-getwd()
setwd(wd)
dir.create(file.path(wd, subDir))
setwd(file.path(wd, subDir))
save.image("init")


###############################################################
## PMMH-SQMC
###############################################################
#Real data example

yySP=read.csv("../Data/SVModel/SP500.csv", sep=",", header=TRUE)
yyN=read.csv("../Data/SVModel/Nasdac.csv", sep=",", header=TRUE)

ySP=as.numeric(as.character(yySP$Close))
yN=as.numeric(as.character(yyN$Close))

ydata=matrix(0,length(yN)-1,2)


for(i in 2:length(yN))
{
	ydata[i-1,1]=log(ySP[i])-log(ySP[i-1])
	ydata[i-1,2]=log(yN[i])-log(yN[i-1])
}

##mean corrected data

y=matrix(0,length(yN)-1,2)

y[,1]=ydata[,1]-mean(ydata[,1])
y[,2]=ydata[,2]-mean(ydata[,2])


dx=ncol(y)
T=nrow(y)

###############################################################
#Prior distribution (assume no leverage effect)

parPrior=c(10*exp(-10), 10*exp(-3)) #parameters of the gamma priors

priorSV=function(t0,dx, dy,par)	    #prior distribution
{
	t=t0

	if(sum(t[(dx+1):(2*dx)]^2<1)==dx & sum(t[(2*dx+1):(3*dx)]>0)==dx)
	{
		#test that we indeed have a correlation matrix

		C=diag(1,2*dx)

		d=1
		for(i in 1:(dx-1))
		{
			for(j in (i+1):(dx))
			{
				C[i,j]=C[j,i]=t[3*dx+d]
				d=d+1
			}
		}

		for(i in (dx+1):(2*dx-1))
		{
			for(j in (i+1):(2*dx))
			{
				C[i,j]=C[j,i]=t[3*dx+d]
				d=d+1
			}
		}

		t1=eigen(C, TRUE, only.values = T, EISPACK = FALSE)$values


		if(sum(t1>0)==2*dx)						
		{
			d=0
	
			for(i in 1:dx)
			{
				d=d-(1+par[1])*log(t[2*dx+i])-par[2]/t[2*dx+i]	
			}

			return(d)
		}else
		{
			return(-Inf)
		}
	}else
	{
		return(-Inf)
	}
}


#put the vector of parameters t0 in the "right" format to be used in "SQMC_SV"

parFilterSV=function(t0,dx,dy)		
{
	t=t0

	mu=t[1:dx]

	Phi=diag(t[(dx+1):(2*dx)],dx)

	Psi=diag(t[(2*dx+1):(3*dx)],dx)

	C=diag(1,2*dx)

	d=1
	for(i in 1:(dx-1))
	{
		for(j in (i+1):(dx))
		{
			C[i,j]=C[j,i]=t[3*dx+d]
			d=d+1
		}
	}

	for(i in (dx+1):(2*dx-1))
	{
		for(j in (i+1):(2*dx))
		{
			C[i,j]=C[j,i]=t[3*dx+d]
			d=d+1
		}
	}
	
	return(c(mu,Phi,Psi,C))
}

###############################################################
#initial value of the MArkov chain

theta0=as.numeric(read.table("../Data/SVModel/theta0.txt")$x)


###############################################################
#parameter of PMMH-SQMC

m=1e4			#length of the Markov chain

#covariance matrix of the gaussian proposal

c=read.table("../Data/SVModel/cov.txt")
c=matrix(as.numeric(as.matrix(c)),8,8)


###############################################################
#PMMH-SQMC
viestimator<-c(1,2,3)
viN<-c(1:10)
vimc<- c(0,1,2)
vmcnames<-c("SMC","SQMC","SAMC")
nrow<-length(viN)
iN=0
for (eN in viN){
for (ie in viestimator){ 
iN=iN+1  
N=10*eN
timer=proc.time()[3]
name<-paste0(vmcnames[[ie]])  
qmc<-vimc[[ie]]
iter=Marginal_PMCMC_anti(y, dx, m, c,  theta0, priorSV, parPrior, N, qmc, parFilterSV, ASQMC_SV)
iter$timer<-proc.time()[3]-timer
print(name) 
print(N)
print("time")
print(iter$timer)
print("acceptance rate")
print(iter$P)					#acceptance rate
print("posterior mean")
print(apply(iter$Y,1,mean))			#posterior mean
print("compute effective sample size")
print(effectiveSize(mcmc(t(iter$Y))))	#compute effective sample size
saveRDS(iter,paste0(name,"_", N ,"_",'PCMC' ,".RDS"))
}
}

















