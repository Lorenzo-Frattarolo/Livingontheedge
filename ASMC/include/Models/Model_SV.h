

#include "../functions.h"
#include "Model_LG.h"


void simPrior_SV(gsl_rng*, int, int, int, double*, double*);
void simPriorQMC_SV(double*, int, int, int, double*, double*);
void simPriorAMC_SV(gsl_rng *, int, int, int, int, double *, double *);
void simPriorAMCmono_SV(double*, int, int, int, double*, double*);


void potential_SV(double*, double*, double*, int,  int, int, int, double*, double*);

double* paramTrans_SV(double*, int, int);
double* paramTransQMC_SV(double*, int, int);


void transition_SV(double*, double*, int, int, int, double*, double*);
