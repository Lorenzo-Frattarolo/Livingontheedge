

#include "../include/functions.h"


int compare_double (const void *pa, const void *pb)
{
	const double *a= pa;
	const double *b= pb;
        if (a[0] > b[0])
                return 1;
        else if (a[0] < b[0])
                 return -1;
       	else
                 return 0;
}


int compare_uint64(const void *pa, const void *pb)
{
	uint64_t a = *(const uint64_t*)pa;
   	uint64_t b = *(const uint64_t*)pb;

        if (a > b)
	{
               	return 1;
	}
       	else if (a < b)
        {
		return -1;
	}
        else
	{
        	return 0;
	}
}

int compare_uint(const void *pa, const void *pb)
{
		
   	unsigned int a = *(unsigned int*)pa;
   	unsigned int b = *(unsigned int*)pb;

        if (a > b)
	{
               	return 1;
	}
        else if (a < b)
        {
		return -1;
	}
        else
	{
             	return 0;
	}
}



double exponen(double x)
{
	double val;
		
	if(x>302.0)
	{
		val = 1e300;
	}
	else if(x<-302.0)
	{
		val = 0.0;
	}
	else
	{
		val = exp(x);
	}

	return(val);
}



double sum(double *vect,int N)
{
	int i;
	double s=0;
	for(i=0;i<N;i++)
	{
		s=s+vect[i];
	}
    return(s);
}


void cumsum(double* vect,int N,double *vect2)
{
	int i=1;
        vect2[0]=vect[0];
	for(i=1;i<N;i++)
	{
		vect2[i]=vect2[i-1]+vect[i];
	}
}



double sum2(double *vect,int N)
{
	int i;
	double s=0;
	for(i=0;i<N;i++)
	{
           s=s+pow(vect[i],2);
	}
    	return(s);
}



//Normalize the importance weights and return the normaliyzing constant

double weight(double *wei, double *W, int N)
{
	double s,acc,nc;
	int i;
	
	s = maxmin(wei,N,1);

	nc = 0.0;
	
	for(i=0;i<N;i++)
	{
		nc += exponen(wei[i]-s);
	}
	
	nc = s + log(nc); 		   
	
	for(i=0;i<N;i++)
	{
		W[i] = exp(wei[i] - nc);  
	}
	return(nc);

}



//Computation of the max/min of a "a" dimensional vector "vec"

double maxmin(double *vec,int a,int b)
{
	double val;
	int i;

	val = vec[0];

	if(b==0)	//minimum
	{
		for(i=1;i<a;i++)
		{
			if(vec[i]<val)
			{
				val = vec[i];
			}	
		}
	}
	else      //maximum
	{
		for(i=1;i<a;i++)
		{
			if(vec[i]>val)
			{
				val = vec[i];
			}	
		}
	}
	
	return(val);
}



//density of multivariate gaussian distribution (with normalizing constant)

double dmnorm_C(const int n, const gsl_vector *x, const gsl_vector *mean, const gsl_matrix *var)
{
	int s;
	double ax,ay;
	gsl_vector *ym, *xm;
	gsl_matrix *work = gsl_matrix_alloc(n,n), 
        *winv = gsl_matrix_alloc(n,n);
	gsl_permutation *p = gsl_permutation_alloc(n);

	gsl_matrix_memcpy( work, var );
	gsl_linalg_LU_decomp( work, p, &s );
	gsl_linalg_LU_invert( work, p, winv );
	ax = gsl_linalg_LU_det( work, s );
	gsl_matrix_free( work );
	gsl_permutation_free( p );
	
	xm = gsl_vector_alloc(n);
	gsl_vector_memcpy( xm, x);
	gsl_vector_sub( xm, mean );
	ym = gsl_vector_alloc(n);
	gsl_blas_dsymv(CblasUpper,1.0,winv,xm,0.0,ym);
	gsl_matrix_free( winv );
	gsl_blas_ddot( xm, ym, &ay);
	gsl_vector_free(xm);
	gsl_vector_free(ym);
	
	ay = -0.5*ay-0.5*n*log(2*M_PI)-0.5*log(ax);

	return ay;
}





void rmnorm(gsl_rng * r, int k, double *mm,  const gsl_matrix *L,double *res)
{
	int i,j;
	gsl_vector *work1 = gsl_vector_alloc(k);
	gsl_vector *work2= gsl_vector_alloc(k); 

	gsl_vector_view m = gsl_vector_view_array(mm,k);
	gsl_vector_memcpy(work1, &m.vector);

	for(i=0;i<k;i++)
	{
		gsl_vector_set(work2,i,gsl_ran_gaussian_ziggurat(r,1));	
	}			
     
	gsl_blas_dgemv (CblasNoTrans, 1,  L, work2, 1, work1);


	for(i=0;i<k;i++)
	{
		res[i]=gsl_vector_get(work1,i);
	}
	gsl_vector_free(work1);
	gsl_vector_free(work2);


}

void rmnormAMC(gsl_rng * r, int k, double *mm,  const gsl_matrix *L,double *res)
{
  int i,j;
  gsl_vector *work1 = gsl_vector_alloc(k);
  gsl_vector *work2= gsl_vector_alloc(k); 
  
  gsl_vector_view m = gsl_vector_view_array(mm,k);
  gsl_vector_memcpy(work1, &m.vector);
  
  for(i=0;i<k;i++)
  {
    gsl_vector_set(work2,i,res[i]);	
  }			
  
  gsl_blas_dgemv (CblasNoTrans, 1,  L, work2, 1, work1);
  
  
  for(i=0;i<k;i++)
  {
    res[i]=gsl_vector_get(work1,i);
  }
  gsl_vector_free(work1);
  gsl_vector_free(work2);
  
  
}



