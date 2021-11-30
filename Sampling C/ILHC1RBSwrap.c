#include <stdio.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include "ILHC1RBS.h"
/*______________________________________________________________________*/
void rndsimpILHRwrap(double *U, mwSize *nv, mwSize *dv, mwSize *tv, int *seed);
/*______________________________________________________________________*/
void rndsimpILHRwrap(double *U, mwSize *nv, mwSize *dv, mwSize *tv, int *seed)  
{
  int n,d,t,i;
  double check,check0;
  n=nv[0];
  d=dv[0];
  t=tv[0];
  double *V=(double*)malloc(sizeof(double)*(n));
  gsl_rng *r=gsl_rng_alloc (gsl_rng_mt19937);
	if(*seed>0)
	{
		gsl_rng_set(r, *seed);
	}
  for (i = 0; i < n; i++){
  double u = gsl_rng_uniform (r);  
  U[i]=u;
  V[i]=u;
  }  
  ILHC1RBS(U, n, d, t, r);
	return;  
}

