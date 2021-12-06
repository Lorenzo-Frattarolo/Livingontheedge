# Livingontheedge
Replication Code for "Living on the Edge: An Unified Approach to Anthitetic Sampling"
Reference: Casarin, R., Craiu, R. V., Frattarolo, L., & Robert, C. P. (2021). Living on the Edge: An Unified Approach to Antithetic Sampling. arXiv preprint arXiv:2110.15124.

Folder Sampling Matlab: 

- Matlab functions for generating random numbers under the different antithetic construction described in the paper
- Uses Shuffle function from https://it.mathworks.com/matlabcentral/fileexchange/27076-shuffle

Folder Sampling R: 

- R functions for generating random numbers under the different antithetic construction described in the paper

Folder Sampling C: 

- C Function and Wrapper for generating random numbers under LH C({1}) 

Folder MC example Matlab : 
- Matlab code for replicating the Monte Carlo integration example of the paper
- Main script wangsloan.m
- reference: Wang, X. and Sloan, I. H. (2005). Why are high-dimensional finance problemsoften of low effective dimension? SIAM Journal on Scientific Computing,27(1):159–183.

Folder MCMC examples matlab : 
- Matlab code for replicating the markov Chain Monte Carlo Bayesian estimation examples of the paper
- Main script Main_Bayes.m
- Plots BayesGraphs_Paper.m
- Bayesian Probit reference: 
van Dyk, D. A. and Meng, X.-L. (2001). The art of data augmentation. Journal of Computational and Graphical Statistics, 10(1):1–50.
- Hierarchical Poisson reference
Gelfand, A. E. and Smith, A. F. M. (1990). Sampling-based approaches to calculating marginal densities. Journal of the American Statistical Association,85(410):398–409.

Folder ASMC : 
- R and C codes for replicating the antithetic sequencial Monte Carlo stochastic volatility example of the paper 
- Code adapted from https://bitbucket.org/mgerber/sqmc/src/master/
- Uses SamplePack Version 0.5,  GSL,  BLAS and  CGAL 4.7
- Main script ASMC/R/SQMC/ASMQPCMC.R
- Plots ASMC/R/SQMC/ASMQPCMC_plots_2020.R
- References:
Chan, D., Kohn, R., and Kirby, C. (2006). Multivariate stochastic volatility models with correlated errors. Econometric Reviews, 25(2-3):245–274.
Gerber, M. and Chopin, N. (2015). Sequential quasi monte carlo. Journal of theRoyal Statistical Society: Series B (Statistical Methodology), 77(3):509–579.
