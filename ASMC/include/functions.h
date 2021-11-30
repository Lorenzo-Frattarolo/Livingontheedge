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

void Def_parameter(double*, int*, int*);

int compare_double (const void*, const void*);
int compare_uint64(const void*, const void*);
int compare_uint(const void*, const void*);

void cumsum(double*,int, double*);
double exponen(double);
double sum(double*,int);
double sum2(double*,int);
double weight(double*,double*,int);
double maxmin(double*,int ,int );

double dmnorm_C(const int, const gsl_vector*, const gsl_vector*, const gsl_matrix*);
void rmnorm(gsl_rng*, int, double*,  const gsl_matrix*,double*);
void rmnormAMC(gsl_rng * , int , double *,  const gsl_matrix *,double *);

