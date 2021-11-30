#include "rndsimpILH.h"
#include <math.h>
#include <inttypes.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_cdf.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
void normrndsimpILH(double *N, mwSize n, mwSize d, mwSize t,gsl_rng *r);
void doublemaxwell(double *R, mwSize n,mwSize nu,gsl_rng *r);