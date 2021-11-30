


#include<stdlib.h>  		
#include<stdio.h>	


#include "Generate_RQMC/generate_RQMC.hpp"	
#include "Resampler/Resampler.h"
#include "functions.h"
#include "SMC.h"



typedef void (*SimTransitionPF_QMC)(double*, double*, int, int, int, int, double*, double*, double*);

typedef void (*SimInitPF_QMC)(double*, int, int, int, double*, double*);	
 
typedef void (*ResamplingPF_QMC)(double*,  double*, int, int, double*, double*);

typedef int* (*ResamplingBack_QMC)(double*, int , double*, int, int, int, double*, double*);

typedef void *DigitalNetGenerator;

typedef void *Scrambled;

/*******************************************************************/

//SQMC Algorithm

void SQMC(double*, int, int, int, double*, int, int, ParamTransitionPF, ResamplingPF_QMC,  SimInitPF_QMC, SimTransitionPF_QMC,
PotentialPF, int*, double*, double*);

void SQMC_Forward(double*, int, int, int, double*, int, int, ParamTransitionPF, ResamplingBack_QMC,  SimInitPF_QMC, SimTransitionPF_QMC,
PotentialPF, int*, double*, double*, double*,  double*, double*);


/*******************************************************************/


void Scrambling(Scrambled*);

void getPoints(Scrambled*, int, int, double*);
 
Scrambled * Scrambled_Create(int,int, int);

void Scrambled_Destroy(Scrambled*);

void Scrambled_Randomize(Scrambled*);

void Scrambled_GetPoints(Scrambled*, int, int, double*);



DigitalNetGenerator *DigitalNetGenerator_Create(int, int);

void DigitalNetGenerator_Destroy(DigitalNetGenerator*); 

void DigitalNetGenerator_GetPoints(DigitalNetGenerator*, int, int, double*); 

void Digital_getPoints(DigitalNetGenerator*, int, int, double*); 


























