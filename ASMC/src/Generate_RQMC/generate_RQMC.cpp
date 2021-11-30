



#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <random>


using namespace std;

#include "../../include/Generate_RQMC/SamplePack/DigitalNetsBase2.h"
#include "../../include/Generate_RQMC/generate_RQMC.hpp"


#define RR 2.328306e-10


typedef  uint32_t    uint;



std::mt19937 mt(getSeed());
std::uniform_real_distribution<double> dist(0.0, 1.0);
   

bitvector rng32()
{
	return (bitvector)(dist(mt)*((double)BV_MAX+1.0));

}

extern "C"{

// interface for the constructor

DigitalNetGenerator *DigitalNetGenerator_Create(int seq, int d) 
{
	dgt gentype;

	if(seq==1)
	{
		gentype=dgt_Sobol;
	}
	else if(seq==2)
	{
		gentype=dgt_SpecialNiederreiter;
	}
	else if(seq==3)
	{
		gentype=dgt_NiederreiterXing;
	}
    	return new DigitalNetGenerator(gentype, d);
}

Scrambled * Scrambled_Create(int seq, int d, int N) 
{
	dgt gentype;

	if(seq==1)
	{
		gentype=dgt_Sobol;
	}
	else if(seq==2)
	{
		gentype=dgt_SpecialNiederreiter;
	}
	else if(seq==3)
	{
		gentype=dgt_NiederreiterXing;
	}
	else
	{
		gentype=dgt_ShiftNet;
	}
	
    	return new Scrambled(gentype, d, N, rng32);
}

// interface for the destructor

void DigitalNetGenerator_Destroy(DigitalNetGenerator* os ) 
{
    delete os;
}


void Scrambled_Destroy(Scrambled* os ) 
{
    delete os;
}


void Scrambled_Randomize(Scrambled *os) 
{
    os->Randomize();
}



void DigitalNetGenerator_GetPoints(DigitalNetGenerator *os, int d, int N, double *x) 
{
	int i,j,k, bucket, index1, index2, index3;

	
	int *J = NULL, *J2 =NULL;
	double *work = NULL;

	if(isPowerOfTwo(N)==1)
	{
		for (i = 0; i < N ; i++)
		{
			bucket=floor(N*(*os)[0]);

			for (k = 0; k < d; k++)
			{
	    			x[bucket*d+k] =(*os)[k]+RR;
			}
			++(*os);
		}
	}
	else
	{
		J = new int[N];
		J2 = new int[N*3];
	 	work = new double[N*d];

		memset(J,0, N*sizeof(int));
	
		for (i = 0; i < N ; i++)
		{
			j=floor(N*(*os)[0]);

			J[j]++;				//number of points in bucket j
	
			J2[3*j+J[j]-1]=i;		//index of the points in bucket j

			for (k = 0; k < d; k++)
			{
	    			work[i*d+k] =(*os)[k]+RR;
			}
			++(*os);
		}

		bucket=0;
		i=0;

		while(i<N)
		{
			if(J[bucket]==1)
			{
				for (k = 0; k < d; k++)
				{
	    				x[i*d+k] =work[J2[3*bucket]*d+k];
				}	
				i++;
			}
			else if (J[bucket]==2)
			{
				index1=0;
				index2=1;

				if(work[J2[3*bucket+1]*d]<=work[J2[3*bucket]*d])
				{
					index1=1;
					index2=0;
				}
			

				for (k = 0; k < d; k++)
				{
	    				x[i*d+k] =work[J2[3*bucket+index1]*d+k];
				}
				i++;
	
				for (k = 0; k < d; k++)
				{
	    				x[i*d+k] =work[J2[3*bucket+index2]*d+k];
				}
				i++;
			
			}
			else if (J[bucket]==3)
			{
				index1=0;
				index2=0;

				for(j=1; j<3; j++)
				{
					if(work[J2[3*bucket+j]*d]<=work[J2[3*bucket+index1]*d])
					{
						index1=j;
					}

					if(work[J2[3*bucket+j]*d]>work[J2[3*bucket+index2]*d])
					{
						index2=j;
					}
				
				}
		
				for (k = 0; k < d; k++)
				{
	    				x[i*d+k] =work[J2[3*bucket+index1]*d+k];
				}

				i++;

				for(j=0; j<3; j++)
				{
					if((j!=index1) && (j!=index2))
					{
						for (k = 0; k < d; k++)
						{
							x[i*d+k] =work[J2[3*bucket+j]*d+k];
						}
					}
				}

				i++;
	
				for (k = 0; k < d; k++)
				{
	    				x[i*d+k] =work[J2[3*bucket+index2]*d+k];
				}
				i++;

			}
			bucket++;

			if(bucket==N)
			{
				break;
			}

		}

		delete [] work;
		work=NULL;

		delete [] J;
		J=NULL;

		delete [] J2;
		J2=NULL;
	}

}





void Scrambled_GetPoints(Scrambled *os, int d, int N, double *x) 
{
	int i,j,k, bucket, index1, index2, index3;

	
	int *J = NULL, *J2 =NULL;
	double *work = NULL;

	if(isPowerOfTwo(N)==1)
	{
		for (i = 0; i < N ; i++)
		{
			bucket=floor(N*(*os)[0]);

			for (k = 0; k < d; k++)
			{
	    			x[bucket*d+k] =(*os)[k]+RR*dist(mt);
			}
			++(*os);
		}
	}
	else
	{
		J = new int[N];
		J2 = new int[N*3];
	 	work = new double[N*d];

		memset(J,0, N*sizeof(int));
	
		for (i = 0; i < N ; i++)
		{
			j=floor(N*(*os)[0]);

			J[j]++;				//number of points in bucket j
	
			J2[3*j+J[j]-1]=i;		//index of the points in bucket j

			for (k = 0; k < d; k++)
			{
	    			work[i*d+k] =(*os)[k]+RR*dist(mt);
			}
			++(*os);
		}

		bucket=0;
		i=0;

		while(i<N)
		{
			if(J[bucket]==1)
			{
				for (k = 0; k < d; k++)
				{
	    				x[i*d+k] =work[J2[3*bucket]*d+k];
				}	
				i++;
			}
			else if (J[bucket]==2)
			{
				index1=0;
				index2=1;

				if(work[J2[3*bucket+1]*d]<=work[J2[3*bucket]*d])
				{
					index1=1;
					index2=0;
				}
			

				for (k = 0; k < d; k++)
				{
	    				x[i*d+k] =work[J2[3*bucket+index1]*d+k];
				}
				i++;
	
				for (k = 0; k < d; k++)
				{
	    				x[i*d+k] =work[J2[3*bucket+index2]*d+k];
				}
				i++;
			
			}
			else if (J[bucket]==3)
			{
				index1=0;
				index2=0;

				for(j=1; j<3; j++)
				{
					if(work[J2[3*bucket+j]*d]<=work[J2[3*bucket+index1]*d])
					{
						index1=j;
					}

					if(work[J2[3*bucket+j]*d]>work[J2[3*bucket+index2]*d])
					{
						index2=j;
					}
				
				}
		
				for (k = 0; k < d; k++)
				{
	    				x[i*d+k] =work[J2[3*bucket+index1]*d+k];
				}

				i++;

				for(j=0; j<3; j++)
				{
					if((j!=index1) && (j!=index2))
					{
						for (k = 0; k < d; k++)
						{
							x[i*d+k] =work[J2[3*bucket+j]*d+k];
						}
					}
				}

				i++;
	
				for (k = 0; k < d; k++)
				{
	    				x[i*d+k] =work[J2[3*bucket+index2]*d+k];
				}
				i++;

			}
			bucket++;

			if(bucket==N)
			{
				break;
			}

		}

		delete [] work;
		work=NULL;

		delete [] J;
		J=NULL;

		delete [] J2;
		J2=NULL;

	}


	


}

};






















