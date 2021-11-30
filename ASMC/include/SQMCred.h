


#include<stdlib.h>  		
#include<stdio.h>	
#include "Generate_RQMC/generate_RQMC.hpp"	
#include "Resampler/Resampler.h"
#include "functions.h"
#include "SMC.h"


typedef void *DigitalNetGenerator;

typedef void *Scrambled;


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


























