/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// SAMPLE PACKage                                                          //
//                                                                         //
// Measurements                                                            //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// Copyright (C) 2002 by Thomas Kollig (kollig@informatik.uni-kl.de)       //
//                       Alexander Keller (keller@informatik.uni-kl.de)    //
//                                                                         //
// All rights reserved. You may not distribute this software, in whole or  //
// in part, especially not as part of any commercial product, without the  //
// express consent of the authors.                                         //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#ifndef MEASUREMENTS_INCLUDED
#define MEASUREMENTS_INCLUDED

extern double *AllocPointMemory(const uint, const uint);
extern void   FreePointMemory(double *, const uint);

extern double StarDiscrepancy(const uint, const uint, double *);
extern double L2Discrepancy(const uint, const uint, double *);
extern double MinimumDistance(const uint, const uint, double *);
extern double MinimumDistanceTorus(const uint, const uint, double *);

extern double CapDiscrepancy(const uint, double *);
extern double MaximumAngle(const uint, double *);
extern double MinimumAngle(const uint, double *);

/////////////////////////////////////////////////////////////////////////////

#endif
