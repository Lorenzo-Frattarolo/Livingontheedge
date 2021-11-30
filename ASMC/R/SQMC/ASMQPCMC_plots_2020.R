

rm(list=ls())


source("../../src/Models/SV_Model/ASQMC_SV.R")

source("../Models.R")

source("../MarginalPMCMC.R") 
require("coda")				#used to compute ESS in PMMH-SQMC
require("ggplot2")	
require("ggpubr")
subDir<-"SAMC_PCMC"
wd<-getwd()
setwd(wd)
setwd(file.path(wd, subDir))

###############################################################
#PMMH-SQMC
viestimator<-c(1,2,3)
viN<-c(1:10)
vimc<- c(0,1,2)
vmcnames<-c("SMC","SQMC","SAMC")
nrow<-length(viN)
nest<-length(viestimator)
ncol<-8
arate<-array(0,dim = c(nrow,nest));
effsize<-array(0,dim = c(nrow,nest,ncol));
meffsize<-array(0,dim = c(nrow,nest));
sdeffsize<-array(0,dim = c(nrow,nest));
maxeffsize<-array(0,dim = c(nrow,nest));
mineffsize<-array(0,dim = c(nrow,nest));
time<-array(0,dim = c(nrow,nest));
iN=0 
for (eN in viN){
  iN=iN+1    
ce=0  
for (ie in viestimator){ 
ce=ce+1
N=10*eN
name<-vmcnames[[ie]]  
qmc<-vimc[[ie]]
con <- paste0(name,"_", N ,"_",'PCMC' ,".RDS")
iter<-readRDS(con)

print(name) 
print(N)
print("acceptance rate")
print(iter$P)					#acceptance rate(
arate[iN,ce]<-iter$P
print(arate[iN,ce])
time[iN,ce]<-iter$timer
print("posterior mean")
print(apply(iter$Y,1,mean))			#posterior mean
print("compute effective sample size")
ef<-effectiveSize(mcmc(t(iter$Y)))
print(ef)	#compute effective sample size
effsize[iN,ce,]<-as.numeric(ef)
meffsize[iN,ce]<-as.numeric(mean(ef))
sdeffsize[iN,ce]<-as.numeric(sd(ef))
maxeffsize[iN,ce]<-as.numeric(max(ef))
mineffsize[iN,ce]<-as.numeric(min(ef))
}
}
vnpart=1:12

require(reshape2)

tt<-data.frame(cbind(as.matrix(10*viN),as.matrix(time)))
colnames(tt)<-c("nparticles",vmcnames[viestimator])
tt_long<-melt(tt,id.vars = "nparticles")
colnames(tt_long)[[3]]<-"time"

aa<-data.frame(cbind(as.matrix(10*viN),arate))
colnames(aa)<-c("nparticles",vmcnames[viestimator])
aa_long<-melt(aa,id.vars = "nparticles" )
colnames(aa_long)[[3]]<-"arate"

mm<-data.frame(cbind(as.matrix(10*viN),meffsize))
colnames(mm)<-c("nparticles",vmcnames[viestimator])
mm_long<-melt(mm,id.vars = "nparticles" )
colnames(mm_long)[[3]]<-"mean"


mmax<-data.frame(cbind(as.matrix(10*viN),maxeffsize))
colnames(mmax)<-c("nparticles",vmcnames[viestimator])
mmax_long<-melt(mmax,id.vars = "nparticles" )
colnames(mmax_long)[[3]]<-"max"

lty <- c("solid", "dashed", "dotted", "dotdash")

mmin<-data.frame(cbind(as.matrix(10*viN),meffsize))
colnames(mmin)<-c("nparticles",vmcnames[viestimator])
mmin_long<-melt(mmin,id.vars = "nparticles" )
colnames(mmin_long)[[3]]<-"min"
data<- merge(merge(merge(merge(mm_long,mmax_long),mmin_long),tt_long),aa_long)
colnames(data)[[2]]<-"Estimator"

bandpart<-ggplot(data=data,mapping=aes(x=nparticles))+
  geom_ribbon(mapping=aes(ymin=min, ymax=max,group=Estimator,fill=Estimator,colour=Estimator,linetype=Estimator),alpha=0.1,size=1)+
  scale_linetype_manual(values=lty)+
  xlab("Number of Particles") + ylab("Effective Size")

bandtime<-ggplot(data=data,mapping=aes(x=time))+
  geom_ribbon(mapping=aes(ymin=min, ymax=max,group=Estimator,fill=Estimator,colour=Estimator,linetype=Estimator),alpha=0.1,size=1)+
  scale_linetype_manual(values=lty)+
  xlab("Time (sec)") + ylab("Effective Size")

apart<-ggplot(data=data,mapping=aes(x=nparticles,y=arate))+
  geom_line(mapping=aes(group=Estimator,colour=Estimator,linetype=Estimator),size=1)+
  geom_point(aes(shape = Estimator,colour=Estimator),size=2) +
  scale_linetype_manual(values=lty)+
  xlab("Number of Particles") + ylab("Acceptance Rate")

atime<-ggplot(data=data,mapping=aes(x=time,y=arate))+
  geom_line(mapping=aes(group=Estimator,colour=Estimator,linetype=Estimator),size=1)+
  geom_point(aes(shape = Estimator,colour=Estimator),size=2) +
  scale_linetype_manual(values=lty)+
  xlab("Time (sec)") + ylab("Acceptance Rate")  

figure <- ggarrange(apart, atime, bandpart,bandtime,
                    labels = c("A", "B", "C","D"),
                    ncol = 2, nrow = 2)
figure
