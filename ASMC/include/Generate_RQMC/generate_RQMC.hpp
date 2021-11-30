

#include"../functionsCC.hpp"

#ifdef _cplusplus 
extern "C" {
	DigitalNetGenerator *DigitalNetGenerator_Create(int, int);
	void DigitalNetGenerator_Destroy(DigitalNetGenerator*); 
	void DigitalNetGenerator_GetPoints(DigitalNetGenerator*, int, int, double*); 

	Scrambled*  Scrambled_Create(int, int, int);
    	void Scrambled_Randomize(Scrambled*);
	void Scrambled_GetPoints(Scrambled*,int, int, double*);
	void Scrambled_Destroy(Scrambled*);
}
 #endif
