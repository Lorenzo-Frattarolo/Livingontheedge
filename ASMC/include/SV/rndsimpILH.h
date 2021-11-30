#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#define mwSize unsigned long long int
void rndsimpILH(double *U, mwSize n, mwSize d, mwSize t,gsl_rng *r);