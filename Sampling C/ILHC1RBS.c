#include "rndsimpILH.h"
void ILHC1RBS(double *U, mwSize n, mwSize d, mwSize t,gsl_rng *r)
{
  double *U1=(double*)malloc(sizeof(double)*(n));
  double *up=(double*)malloc(sizeof(double)*(d));
  double *UU=(double*)malloc(sizeof(double)*(n*(d)));
  mwSize i,j,k;
  double tmp,tmp2;
  for (j = 0; j < d; j++){
  for (i = 0; i < n; i++){ 
    if (j==0) {
      double u = gsl_rng_uniform (r);
      U1[i]=u;
      UU[i+j*n]=u;
    }
    else {
      UU[i+j*n]= (((double)j)-U1[i])/((double)(d-1));
    }
  }
  }
  free(U1);
  U1=NULL;
        for (i = 0; i < n; i++){
          for (j = 0; j < d; j++){   
        tmp=UU[i+j*n];
        up[j]= tmp;
    }
        gsl_ran_shuffle (r, up, d, sizeof (double)); 
        for (j = 0; j < d; j++){ 
        tmp=up[j];
        UU[i+j*n]= tmp;
      }
    }
       
       for (k = 0; k < t; k++){ 
         for (j = 0; j < d; j++){   
           up[j]= j;
         } 
         for (i = 0; i < n; i++){
           gsl_ran_shuffle (r, up, d, sizeof (double));
           for (j = 0; j < d; j++){   
             tmp=UU[i+j*n];
             tmp2=up[j];
             UU[i+j*n]= (tmp2+tmp)/((double)d);
           }
         }
       } 
       free(up);
       up=NULL;
        for (j = 0; j < d; j++){ 
          for (i = 0; i < n; i++){
            tmp=UU[i+j*n];
            U[i+j*n]=tmp;
          }
        }
        free(UU);
        UU=NULL;
}
