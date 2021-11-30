
	
#include <stdlib.h>
#include <gsl/gsl_heapsort.h> 
  		
#include "HilbertCode.hpp"


#include "../../functions.h"


void HilbertResampler(double*,   double*, int, int, double*, double*);

int *ForHilbertResampler(double*, int,  double*,  int, int, int, double*, double*);
	
int *BackHilbertResampler(double*, int,  double*,  int, int, int, double*, double*);


void quasi_Resample(double*, int ,int , double*, size_t *, double*, double*);
void quasi_ResampleFor(double*, int , int , int, int, double*, size_t*,  double*, double*);

void quasi_ResampleBack(double*, int , int, int, int, double*, size_t*,int*, double*, double*);



