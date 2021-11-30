


#include<stdlib.h>  		
#include<stdio.h>	


#include "Resampler/Resampler.h"
#include "functions.h"
#include "SMC.h"
#include "SQMC.h"



typedef void (*SimTransitionPF_QMC)(double*, double*, int, int, int, int, double*, double*, double*);

typedef void (*SimInitPF_QMC)(double*, int, int, int, double*, double*);	

typedef void (*ResamplingPF_AMC)(double* , int ,  int , double* , size_t*, double* , double* );

//typedef int (*ResamplingPF_index)(gsl_rng*, double*, int, int, int, double*, double*);

 
//typedef void (*ResamplingPF)(gsl_rng*, double*, int, int, int, double*, double*);
 
//typedef int* (*ResamplingBack_QMC)(double*, int , double*, int, int, int, double*, double*);


/*******************************************************************/

//SQMC Algorithm

void ASMC(double*, int, int, int, double*, int, int, gsl_rng*, ParamTransitionPF, ResamplingPF,  SimInitPF_QMC, SimTransitionPF_QMC,
PotentialPF, int*, double*, double*);



/*******************************************************************/


























