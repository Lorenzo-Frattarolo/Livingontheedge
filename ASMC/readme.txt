### SOFTWARE TO IMPLEMENT ANTITHETIC SEQUENTIAL MONTE CARLO ###

Reference: Casarin, R., Craiu, R. V., Frattarolo, L., & Robert, C. P. (2021). Living on the Edge: An Unified Approach to Antithetic Sampling. arXiv preprint arXiv:2110.15124.



The code is adapted from https://bitbucket.org/mgerber/sqmc/src/master/

Reference: [M. Gerber and N. Chopin (2015), Sequential quasi-Monte Carlo, Journal of the Royal Statistical Society, 77(3), 509–579](http://onlinelibrary.wiley.com/doi/10.1111/rssb.12104/abstract)
	    	  
** Note that the code has only been tested on Linux Ubuntu 14.04 LTS (64 bits)**


#Contents: 

Folder "ASMC"

	** The stochastic volatility example of the paper "Living on the Edge: An Unified Approach to Antithetic Sampling" 
	

######################################################################################################
#Libraries

The code uses the following program:

** SamplePack Version 0.5 (available at http://www.uni-kl.de/AG-Heinrich/SamplePack.html): 

	Copyright 2002 by Thomas Kollig <kollig@informatik.uni-kl.de>      
	and Alexander Keller <keller@informatik.uni-kl.de)    
	
In addition, the code refers to GSL, and by extention to BLAS, and to CGAL 4.7

########################################################################################################