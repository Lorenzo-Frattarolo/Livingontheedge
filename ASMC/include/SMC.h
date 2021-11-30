

#include <stdlib.h>  //malloc	
#include <gsl/gsl_rng.h>

#include "functions.h"
#include "Resampler/Resampler.h"

					
typedef void (*SimInitPF)(gsl_rng*, int, int,int, double*, double*);				

typedef double* (*ParamTransitionPF)(double*, int, int);

typedef void (*TransitionPF)(double*, double*, int, int, int, double*, double*);			

typedef void (*SimTransitionPF)(gsl_rng*, double*, int, int, int, int, double*, double*, double*);			

typedef void (*PotentialPF)(double*, double*, double*, int, int, int, int, double*, double*);			
			  
typedef void (*ResamplingPF)(gsl_rng*, double*, int, int, int, double*, double*);


			
void SMC(double*, int, int, int, double*, int, gsl_rng*, ParamTransitionPF, ResamplingPF, SimInitPF, SimTransitionPF, PotentialPF, int*, double*, double*);

void SMC_Forward(double*, int, int, int, double*, int, gsl_rng*, ParamTransitionPF, ResamplingPF, SimInitPF, SimTransitionPF, 
PotentialPF, int*, double*, double*,double*, double*, double*);



