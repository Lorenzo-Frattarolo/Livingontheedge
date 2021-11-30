
#include <R.h>
#include "../include/ASMC.h"
#include <omp.h>
#include "../include/SV/rndsimpILH.h"
#include "../include/Resampler/Hilbert_Resampler/HilbertResamplerQMC.h"
/****************************************************************************************************
				ANTITHETIC SEQUENTIAL MONTE CARLO	

Output: Estimate of the log-likelihood function at each time steps ans filtering expectations
******************************************************************************************************/


void ASMC(double *y, int dy, int dx, int T, double *theta, int N, int il, gsl_rng* r, ParamTransitionPF paramTransition, ResamplingPF resampling,
 SimInitPF_QMC simInit,  SimTransitionPF_QMC simTransition, PotentialPF potential, int* par, double *lik, double *expx)
{
	int i,j,k,iter;
	double cc;
     double *wei=(double*)malloc(sizeof(double)*N);
	double *W=(double*)malloc(sizeof(double)*N);
	double *x=(double*)malloc(sizeof(double)*(N*dx));
	double *xh=(double*)malloc(sizeof(double)*(N*dx));
	double *sim=(double*)malloc(sizeof(double)*(N*(dx+1)));
	double *sim2=(double*)malloc(sizeof(double)*(N*(dx+1)));
	double *sim3=(double*)malloc(sizeof(double)*(N*(dx)));
	double *param=NULL;
	
	
	

	
	iter=0;
  rndsimpILH(sim, dx,N ,  il, r);  
  
  
  
	
	
			(*simInit)(sim, dx, dy, N, theta, x);

			//Evaluate the potential function

			(*potential)(y, x, xh, dy, dx, 0, N, theta, wei);

			//Normalize the weights and compute log-likelihood

			lik[0]=weight(wei, W, N)-log(N);
	
			//Compute filtering expectation
		
			if(par[0]==1)
			{
				for(k=0;k<dx;k++)
				{
					cc=0;
					for(i=0;i<N;i++)
					{
						cc+=W[i]*x[dx*i+k];
					}
					expx[k]=cc;
				}
			}
		
			//Compute parameters of the Markov transition 
		
			param=(*paramTransition)(theta,dx,dy);
		
	for(iter=1;iter< T;iter++)
	{
		
			  rndsimpILH(sim3, dx, N, il, r);
	      int ii,jj;
	      for(jj=0;jj<N;jj++){
	      for(ii=0;ii<dx+1;ii++){
	        if (ii>= 1){   
	            sim2[(dx+1)*jj+ii]=sim3[(dx)*jj+(ii-1)];
	          
	        }else{
	          sim2[(dx+1)*jj+ii]=0;  
	        } 
	        }   
	      }
	      
	      
				(*resampling)(r, x, dx, N, N, W, xh); 
				
				
				//Mutation
				(*simTransition)(sim2, y, dy, dx, iter, N, param, xh, x); 

				//Evaluate the potential function
		
				(*potential)(y, x, xh, dy, dx, iter, N, theta, wei);   
				if (isnan(sum(wei,N))){
				  printf("lik %f iter %d ",lik[iter], iter );
				  printf(" w Wei ");
				  for(jj=0;jj<N;jj++){
				    printf(" wei %f  W %f ", wei[jj], W[jj]);
				  }
				  printf(" \n ");
				  
				  printf(" sim3 ");
				  for(jj=0;jj<N;jj++){
				    for(ii=0;ii<dx;ii++){  
				      printf(" sim3 %f %d %d ", sim3[jj*(dx)+ii], jj, ii);
				    }
				    printf(" \n ");  
				  }
				  
				  
				  printf(" sim2 ");
				  for(jj=0;jj<N;jj++){
				    for(ii=0;ii<dx+1;ii++){  
				      printf(" sim2 %f %d %d ", sim2[jj*(dx+1)+ii],jj ,ii);
				    }
				    printf(" \n ");  
				  }
				  
				  
				  printf(" x ");
				  for(ii=0;ii<dx;ii++){
				    for(jj=0;jj<N;jj++){
				      printf(" x %f ", x[jj+ii*N]);
				    }
				  }
				  printf(" \n ");
				  
				  
				  getchar();  
				}
			
				//Nomalize the weights and compute log-likelihood

				lik[iter]=lik[iter-1]+weight(wei,W,N)-log(N);

				//Compute filtering expectation

				if(par[0]==1)
				{
					for(k=0;k<dx;k++)
					{
						cc=0;
						for(i=0;i<N;i++)
						{
							cc+=W[i]*x[dx*i+k];
						}
						expx[dx*iter+k]=cc;
					}
				}
			
	}


	
	free(param);
	param=NULL;
	free(wei);
	wei=NULL;
	free(W);
	W=NULL;
	free(x);
	x=NULL;
	free(xh);
	xh=NULL;
	free(sim);
	sim=NULL;
	free(sim2);
	sim2=NULL;
	free(sim3);
	sim3=NULL;
}







