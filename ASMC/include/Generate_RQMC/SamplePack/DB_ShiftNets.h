/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// SAMPLE PACKage                                                          //
//                                                                         //
// Digital nets in base 2                                                  //
// Shift-net definitions                                                   //
//                                                                         //
//                                                                         //
// These values are taken from                                             //
//                                                                         //
// W. Ch. Schmid,                                                          //
// "Shift-nets: a new class of binary digital (t, m, s)-nets",             //
// in P. Hellekalek, G. Larcher, H. Niederreiter, and P. Zinterhof (eds.), //
// Monte Carlo and Quasi-Monte Carlo Methods in Scientific Computing,      //
// volume 127 of Lecture Notes in Statistics,                              //
// Springer-Verlag, New York, 1997, pp. 369-381                            //
//                                                                         //
// and by kind permission included here.                                   //
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

//                          k,   the first k rows of C(0) of the (m - k, m, m)-shift-net
const int tms_0_3_3[]    = {3,   1, 6, 2};
const int tms_1_4_4[]    = {3,   1, 6, 2};
const int tms_1_5_5[]    = {4,   1, 14, 18, 2};
const int tms_2_6_6[]    = {4,   1, 14, 18, 2};
const int tms_2_7_7[]    = {5,   1, 46, 26, 6, 2};
const int tms_3_8_8[]    = {5,   1, 46, 26, 6, 2};
const int tms_3_9_9[]    = {6,   1, 94, 178, 38, 10, 2};
const int tms_4_10_10[]  = {6,   1, 94, 170, 38, 10, 2};
const int tms_4_11_11[]  = {7,   1, 492, 1638, 86, 14, 18, 2};
const int tms_5_12_12[]  = {7,   1, 378, 590, 158, 42, 6, 2};
const int tms_6_13_13[]  = {7,   1, 366, 572, 154, 14, 18, 2};
const int tms_6_14_14[]  = {8,   1, 734, 10652, 372, 46, 22, 10, 2};
const int tms_7_15_15[]  = {8,   1, 734, 3308, 372, 46, 22, 10, 2};
const int tms_8_16_16[]  = {8,   1, 758, 3132, 414, 46, 22, 10, 2};
const int tms_8_17_17[]  = {9,   1, 3562, 29276, 870, 62, 198, 74, 6, 2};
const int tms_9_18_18[]  = {9,   1, 3450, 9814, 2020, 458, 54, 26, 6, 2};
const int tms_10_19_19[] = {9,   1, 3562, 8566, 1884, 236, 30, 38, 10, 2};
const int tms_10_20_20[] = {10,  1, 10094, 301178, 17650, 2300, 314, 78, 22, 10, 2};
const int tms_11_21_21[] = {10,  1, 10106, 54364, 3974, 4214, 158, 294, 42, 62, 2};
const int tms_12_22_22[] = {10,  1, 10198, 54476, 18296, 2674, 124, 150, 26, 6, 2};
// 23 <= m <= 39, k = 10
const int tms_m_10_m_m[] = {10,  1, 10094, 51322, 22822, 190, 626, 270, 22, 10, 2};

const int *ShiftNet[] =
{ NULL, 
  NULL, 
  NULL,
  tms_0_3_3,
  tms_1_4_4,
  tms_1_5_5,
  tms_2_6_6,
  tms_2_7_7,
  tms_3_8_8,
  tms_3_9_9,
  tms_4_10_10,
  tms_4_11_11,
  tms_5_12_12,
  tms_6_13_13,
  tms_6_14_14,
  tms_7_15_15,
  tms_8_16_16,
  tms_8_17_17,
  tms_9_18_18,
  tms_10_19_19,
  tms_10_20_20,
  tms_11_21_21,
  tms_12_22_22,
  tms_m_10_m_m };
