/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// SAMPLE PACKage                                                          //
//                                                                         //
// Radical inverses in base 2                                              //
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

#ifndef RADICALINVERSESBASE2_INCLUDED
#define RADICALINVERSESBASE2_INCLUDED

typedef unsigned int uint;

/////////////////////////////////////////////////////////////////////////////

inline double RI_vdC(uint bits, uint r = 0)
{
  bits = ( bits               << 16) | ( bits               >> 16);
  bits = ((bits & 0x00ff00ff) <<  8) | ((bits & 0xff00ff00) >>  8);
  bits = ((bits & 0x0f0f0f0f) <<  4) | ((bits & 0xf0f0f0f0) >>  4);
  bits = ((bits & 0x33333333) <<  2) | ((bits & 0xcccccccc) >>  2);
  bits = ((bits & 0x55555555) <<  1) | ((bits & 0xaaaaaaaa) >>  1);
  bits ^= r;
  return (double)bits / (double)0x100000000LL;
}

inline double RI_S(uint i, uint r = 0)
{
  for (uint v = 1<<31; i; i >>= 1, v ^= v>>1)
    if (i & 1)
      r ^= v;
  return (double)r / (double)0x100000000LL;
}

inline double RI_LP(uint i, uint r = 0)
{
  for (uint v = 1<<31; i; i >>= 1, v |= v>>1)
    if (i & 1)
      r ^= v;
  return (double)r / (double)0x100000000LL;
}

inline double RI_Bn(uint i, uint n, uint r = 0) // ;-)
{
  r ^= i * (0x100000000LL / n);
  return (double)r / (double)0x100000000LL;
}

/////////////////////////////////////////////////////////////////////////////

#endif
