# options
CFLAGS= -I/usr/share/R/include -fpic -O3 -pipe -g -c -fopenmp -frounding-math 

all: lib/SV_ASQMC.so  


# SV model


lib/SV_ASQMC.so: SV_Model.o LG_Model.o HilbertResamplerQMC.o Resampler.o functions.o  functionsCC.o HilbertCode.o  SMC.o SMC_Back.o SQMC.o SQMC_Back.o generate_RQMC.o DigitalNetsBase2.o rndsimpILH.o normrndsimpILH.o ASMC.o SV_ASQMC.o rndsimpILHRwrap.o 
	g++ -shared -o lib/SV_ASQMC.so  SV_Model.o LG_Model.o HilbertResamplerQMC.o Resampler.o functions.o  functionsCC.o HilbertCode.o  SMC.o SMC_Back.o SQMC.o SQMC_Back.o  generate_RQMC.o DigitalNetsBase2.o ASMC.o SV_ASQMC.o rndsimpILH.o normrndsimpILH.o rndsimpILHRwrap.o  -lgsl -lgslcblas -lCGAL -fopenmp -L/usr/lib/R/lib -lR



## Sample Pack

DigitalNetsBase2.o: src/Generate_RQMC/SamplePack/DigitalNetsBase2.C
	g++ $(CFLAGS) src/Generate_RQMC/SamplePack/DigitalNetsBase2.C -o DigitalNetsBase2.o

generate_RQMC.o: src/Generate_RQMC/generate_RQMC.cpp
	g++ -std=c++0x $(CFLAGS) src/Generate_RQMC/generate_RQMC.cpp -o generate_RQMC.o

## Some useful functions

functionsCC.o: src/functionsCC.cpp
	g++ $(CFLAGS) src/functionsCC.cpp -o functionsCC.o

functions.o: src/functions.c
	gcc $(CFLAGS) src/functions.c -o functions.o

## Simplicial Variates
rndsimpILH.o: src/rndsimpILH.c
	gcc $(CFLAGS) src/rndsimpILH.c -o rndsimpILH.o	

normrndsimpILH.o: src/normrndsimpILH.c
	gcc $(CFLAGS) src/normrndsimpILH.c -o normrndsimpILH.o	

rndsimpILHRwrap.o: src/rndsimpILHRwrap.c
	gcc $(CFLAGS) src/rndsimpILHRwrap.c -o rndsimpILHRwrap.o		



## Hilbert resampling

HilbertResamplerQMC.o: src/Resampler/Hilbert_Resampler/HilbertResamplerQMC.c
	gcc $(CFLAGS) src/Resampler/Hilbert_Resampler/HilbertResamplerQMC.c -o HilbertResamplerQMC.o

Resampler.o: src/Resampler/Resampler.c
	gcc $(CFLAGS) src/Resampler/Resampler.c -o Resampler.o

HilbertCode.o: src/Resampler/Hilbert_Resampler/HilbertCode.cpp
	g++ $(CFLAGS)  src/Resampler/Hilbert_Resampler/HilbertCode.cpp -o HilbertCode.o


## Particles filters algorithms

SMC.o: src/SMC.c
	gcc $(CFLAGS) src/SMC.c -o SMC.o

SMC_Back.o: src/SMC_Back.c
	gcc $(CFLAGS) src/SMC_Back.c -o SMC_Back.o

SQMC.o: src/SQMC.c
	gcc $(CFLAGS) src/SQMC.c -o SQMC.o

SQMC_Back.o: src/SQMC_Back.c
	gcc $(CFLAGS) src/SQMC_Back.c -o SQMC_Back.o

ASMC.o: src/ASMC.c
	gcc $(CFLAGS) src/ASMC.c -o ASMC.o
	

## Models

LG_Model.o: src/SMC.c
	gcc $(CFLAGS) src/Models/LinearGaussian_Model/LG_Model.c -o LG_Model.o

SV_Model.o: src/Models/SV_Model/SV_Model.c
	gcc $(CFLAGS) src/Models/SV_Model/SV_Model.c -o SV_Model.o

SV_ASQMC.o: src/Models/SV_Model/SV_ASQMC.c
	gcc $(CFLAGS) src/Models/SV_Model/SV_ASQMC.c -o SV_ASQMC.o



# clean

clean: 
	find . -type f -name '*.o' -delete
