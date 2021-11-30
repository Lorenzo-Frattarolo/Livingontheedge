/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// SAMPLE PACKage                                                          //
//                                                                         //
// Digital nets in base 2                                                  //
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

#ifndef DIGITALNETSBASE2_INCLUDED
#define DIGITALNETSBASE2_INCLUDED

#define _INCLUDE_LONGLONG

#include <string.h>
#include <iostream>
#include <math.h>
#include <inttypes.h>

using namespace std;

class Polynomial;
class GeneratorMatrices;
class DigitalNetGenerator;
class DigitScrambled;
class LinearScrambled;
class Scrambled;

typedef uint32_t      bitvector;
typedef unsigned long long longbitvector;
typedef unsigned int       uint;
typedef unsigned long long ulonglong;

typedef bitvector bvrand();

#define BV_BYTES   (sizeof(bitvector))
#define BV_BITS    (8*BV_BYTES)
#define BV_MAXBIT  (((bitvector)1 << (BV_BITS-1)))
#define BV_MAX     ((bitvector)-1)
#define BV_RES     (1.0/((double)BV_MAX+1.0))
#define LBV_BYTES  (sizeof(longbitvector))
#define LBV_BITS   (8*LBV_BYTES)
#define LBV_MAXBIT (((longbitvector)1 << (LBV_BITS-1)))
#define LBV_MAX    ((longbitvector)-1)
#define LBV_RES    (1.0/((double)LBV_MAX+1.0))

typedef enum _dgt
{
  dgt_Sobol, 
  dgt_SpecialNiederreiter,
  dgt_NiederreiterXing,
  dgt_ShiftNet
} dgt;

/////////////////////////////////////////////////////////////////////////////

inline uint GrayCodeChange(uint i)
{
  uint pos, c;
  
  for (pos = 0, c = 1; !(i & c); ++pos, c <<= 1);
  
  return pos;
}

/////////////////////////////////////////////////////////////////////////////

class Polynomial
{
  longbitvector p;
  
public:
  
  inline Polynomial();
  inline Polynomial(const longbitvector);
  
  inline operator longbitvector() const;
  
  inline        Polynomial operator+(const Polynomial) const;
  inline        Polynomial &operator+=(const Polynomial);
  inline        Polynomial operator*(Polynomial) const;
  inline        Polynomial &operator*=(Polynomial);
  inline        Polynomial operator/(Polynomial) const;
  inline        Polynomial &operator/=(Polynomial);
  inline        Polynomial operator%(Polynomial) const;
  inline        Polynomial &operator%=(Polynomial);
  inline        Polynomial operator+(const longbitvector) const;
  inline        Polynomial &operator+=(const longbitvector);
  inline        Polynomial operator<<(const longbitvector) const;
  inline        Polynomial &operator<<=(const longbitvector);
  inline        Polynomial operator>>(const longbitvector) const;
  inline        Polynomial &operator>>=(const longbitvector);
  inline        bool       operator<(const longbitvector) const;
  inline        bool       operator<=(const longbitvector) const;
  inline        bool       operator>(const longbitvector) const;
  inline        bool       operator>=(const longbitvector) const;
  inline friend ostream    &operator<<(ostream &, const Polynomial &);
  
  inline int  Degree() const;
  inline bool IsIrreducible() const;
  inline bool IsPrimitive() const;
};

class GeneratorMatrices
{
  uint      dimension;
  bitvector *data;

public:
  
  inline GeneratorMatrices();
  inline GeneratorMatrices(const uint);
  inline ~GeneratorMatrices();

  inline GeneratorMatrices &operator=(const GeneratorMatrices &);
  inline GeneratorMatrices operator*(const GeneratorMatrices &) const;
  
  void Initialize(const uint);
  void Initialize(const uint, const bitvector *);
  int  Load(const char *);
  void Save(const char *) const;
  void Print(ostream &, const int, const bool) const;
  
  inline uint      GetDimension() const;
  inline bitvector GetRow(const uint, const uint) const;
  inline void      SetRow(const uint, const uint, bitvector) const;
  inline bitvector GetColumn(const uint, const uint) const;
  inline void      SetColumn(const uint, const uint, bitvector) const;
  inline bitvector *GetColumns(const uint) const;
};

class DigitalNetGenerator
{
protected:

  GeneratorMatrices gm;
  bitvector         count;
  bitvector         *state;
  double            *qrn;
  
  void InitSobol(const uint);
  void InitSpecialNiederreiter(const uint);
  void InitNiederreiterXing(const uint);
  void InitShiftNet(const uint);

public:

  DigitalNetGenerator(const uint);
  DigitalNetGenerator(const char *);
  DigitalNetGenerator(const dgt, const uint);
  ~DigitalNetGenerator();
  
  inline DigitalNetGenerator &operator++();
  inline double              &operator[](const uint) const;
  
  inline void Reset();

  uint GettParameter(const uint, const uint) const;
  void UndoGray();
};

class DigitScrambled
  : public DigitalNetGenerator
{
  bvrand *r;
  
public:

  DigitScrambled(const char *, bvrand &);
  DigitScrambled(const dgt, const uint, bvrand &);
  
  inline void Randomize();
};

class LinearScrambled
  : public DigitalNetGenerator
{
  GeneratorMatrices originalgm;
  bvrand            *r;
  
public:
  
  LinearScrambled(const char *, bvrand &);
  LinearScrambled(const dgt, const uint, bvrand &);
  
  inline void Randomize();
};

class Scrambled
  : public DigitalNetGenerator
{
  uint      n;
  bitvector *data;
  bvrand    *r;
  
public:
  
  Scrambled(const char *, const uint, bvrand &);
  Scrambled(const dgt, const uint, const uint, bvrand &);
  ~Scrambled();
  
  inline Scrambled &operator++();
  
  inline void Randomize();
};

/////////////////////////////////////////////////////////////////////////////

inline Polynomial::Polynomial()
{
  p = 0;
}

inline Polynomial::Polynomial(const longbitvector lbv)
{
  p = lbv;
}

inline Polynomial::operator longbitvector() const
{
  return p;
}

inline Polynomial Polynomial::operator+(const Polynomial q) const
{
  return p ^ q.p;
}

inline Polynomial &Polynomial::operator+=(const Polynomial q)
{
  p ^= q.p;
  return *this;
}

inline Polynomial Polynomial::operator*(Polynomial q) const
{
  longbitvector erg = 0;
  longbitvector pf;

  for (pf = p; q.p; q.p >>= 1, pf <<= 1)
    if (q.p & 1)
      erg ^= pf;  
  return Polynomial(erg);
}

inline Polynomial &Polynomial::operator*=(Polynomial q)
{
  longbitvector pf;
  
  for (pf = p, p = 0; q.p; q.p >>= 1, pf <<= 1)
    if (q.p & 1)
      p ^= pf;
  return *this;
}

inline Polynomial Polynomial::operator/(Polynomial q) const
{
  longbitvector f;
  longbitvector tmp = p;
  longbitvector erg = 0;
  
  for (f = 1; (q.p & LBV_MAXBIT) == 0; q.p <<= 1, f <<= 1);
  for (; f; q.p >>= 1, f >>= 1)
    if ((tmp ^ q.p) < tmp)
      {
	tmp ^= q.p;
	erg ^= f;
      }
  return erg;
}

inline Polynomial &Polynomial::operator/=(Polynomial q)
{
  longbitvector f;
  longbitvector tmp = p;
 
  p = 0;
  for (f = 1; (q.p & LBV_MAXBIT) == 0; q.p <<= 1, f <<= 1);
  for (; f; q.p >>= 1, f >>= 1)
    if ((tmp ^ q.p) < tmp)
      {
	tmp ^= q.p;
	p ^= f;
      }
  return *this;
}

inline Polynomial Polynomial::operator%(Polynomial q) const
{
  longbitvector f;
  longbitvector erg = p;
  
  for (f = 1; (q.p & LBV_MAXBIT) == 0; q.p <<= 1, f <<= 1);
  for (; f; q.p >>= 1, f >>= 1)
    if ((erg ^ q.p) < erg)
      erg ^= q.p;
  return erg;
}

inline Polynomial &Polynomial::operator%=(Polynomial q)
{
  longbitvector f;

  for (f = 1; (q.p & LBV_MAXBIT) == 0; q.p <<= 1, f <<= 1);
  for (; f; q.p >>= 1, f >>= 1)
    if ((p ^ q.p) < p)
      p ^= q.p;
  return *this;
}

inline Polynomial Polynomial::operator+(const longbitvector lbv) const
{
  return p + lbv;
}

inline Polynomial &Polynomial::operator+=(const longbitvector lbv)
{
  p += lbv;
  return *this;
}

inline Polynomial Polynomial::operator<<(const longbitvector lbv) const
{
  return p << lbv;
}

inline Polynomial &Polynomial::operator<<=(const longbitvector lbv)
{
  p <<= lbv;
  return *this;
}

inline Polynomial Polynomial::operator>>(const longbitvector lbv) const
{
  return p >> lbv;
}

inline Polynomial &Polynomial::operator>>=(const longbitvector lbv)
{
  p >>= lbv;
  return *this;
}

inline bool Polynomial::operator<(const longbitvector lbv) const
{
  return p < lbv;
}

inline bool Polynomial::operator<=(const longbitvector lbv) const
{
  return p <= lbv;
}

inline bool Polynomial::operator>(const longbitvector lbv) const
{
  return p > lbv;
}

inline bool Polynomial::operator>=(const longbitvector lbv) const
{
  return p >= lbv;
}

inline ostream& operator<<(ostream &s, const Polynomial &p)
{
  int           i;
  longbitvector pf;
  
  for (i = LBV_BITS, pf = LBV_MAXBIT; i > 0; --i, pf >>= 1)
    if (p.p & pf)
      cout << "1";
    else
      cout << "0";
  return s;
}

inline int Polynomial::Degree() const
{
  int           i;
  longbitvector lbv;

  for (i = -1, lbv = LBV_MAX; lbv & p; ++i, lbv <<= 1);
  return i;
}

inline bool Polynomial::IsIrreducible() const
{
  if (p & 1)
    {
      Polynomial q; 
      for (q = 3; q*q <= p; q += 2)
	if ((*this % q).p == 0)
	  return false;
      return true;
    }
  else
    return false;
}

inline bool Polynomial::IsPrimitive() const
{
  if (IsIrreducible())
    {
      int        i;
      Polynomial q(1);
      for (i = (1 << Degree())-2; i > 0; --i)
	{
	  q.p <<= 1;
	  q %= p;
	  if (q.p == 1)
	    return false;
	}
      return true;
    }
  else
    return false;
}

/////////////////////////////////////////////////////////////////////////////

inline GeneratorMatrices::GeneratorMatrices()
{
  data = NULL;
}

inline GeneratorMatrices::GeneratorMatrices(const uint s)
{
  dimension = s;
  data = new bitvector[dimension*BV_BITS];
}

inline GeneratorMatrices::~GeneratorMatrices()
{
  if (data)
    delete []data;
}

inline GeneratorMatrices &GeneratorMatrices::operator=
(const GeneratorMatrices &gm)
{
  if (data)
    delete []data;
  dimension = gm.GetDimension();
  data = new bitvector[dimension*BV_BITS];
  memcpy(data, gm.data, dimension*BV_BITS*BV_BYTES);
  return *this;
}

inline GeneratorMatrices GeneratorMatrices::operator*
(const GeneratorMatrices &gm) const
{
  uint              i, j, k;
  bitvector         row, ergrow;
  GeneratorMatrices erg(dimension);
  
  for (i = 0; i < dimension; ++i)
    for (j = 0; j < BV_BITS; ++j)
      {
	ergrow = 0;
	for (row = GetRow(i, j), k = 0; row; row <<= 1, ++k)
	  if (row & BV_MAXBIT)
	    ergrow ^= gm.GetRow(i, k);
	erg.SetRow(i, j, ergrow);
      }
  return erg;
}

inline uint GeneratorMatrices::GetDimension() const
{
  return dimension;
}
  
inline bitvector GeneratorMatrices::GetRow(const uint d, const uint r) const
{
  bitvector erg;
  bitvector pos;
  bitvector row;
  bitvector *column;
  
  erg = 0;
  row = (BV_MAXBIT >> r);
  for (pos = BV_MAXBIT, column = data+d;
       pos;
       pos >>= 1, column += dimension)
    if (*column & row)
      erg |= pos;
  return erg;
}

inline void GeneratorMatrices::SetRow
(const uint d, const uint r, const bitvector bv) const
{
  bitvector pos;
  bitvector row;
  bitvector *column;
  
  row = (BV_MAXBIT >> r);
  for (pos = BV_MAXBIT, column = data+d;
       pos;
       pos >>= 1, column += dimension)
    if (bv & pos)
      *column |= row;
    else
      *column &= ~row;
}

inline bitvector GeneratorMatrices::GetColumn
(const uint d, const uint c) const
{
  return *(data + c*dimension + d);
}

inline void GeneratorMatrices::SetColumn
(const uint d, const uint c, bitvector bv) const
{
  *(data + c*dimension + d) = bv;
}

inline bitvector *GeneratorMatrices::GetColumns(const uint c) const
{
  return data + c*dimension;
}

/////////////////////////////////////////////////////////////////////////////

inline DigitalNetGenerator &DigitalNetGenerator::operator++()
{
  uint      i, pos;
  bitvector bv, *columns;
  
  ++count;
  for (pos = 0, bv = 1; !(count & bv); ++pos, bv <<= 1);
  columns = gm.GetColumns(pos);
  for (i = 0; i < gm.GetDimension(); ++i)
    {
      state[i] ^= *columns;
      ++columns;
      qrn[i] = (double)state[i] * BV_RES;
    }
  return *this;
}

inline double &DigitalNetGenerator::operator[](const uint d) const
{
  return qrn[d];
}

inline void DigitalNetGenerator::Reset()
{
  uint i;
  
  count = 0;
  for (i = 0; i < gm.GetDimension(); ++i)
    {
      state[i] = 0;
      qrn[i] = 0.0;
    }
}

/////////////////////////////////////////////////////////////////////////////

inline void DigitScrambled::Randomize()
{
  uint i;
  
  count = 0;
  for (i = 0; i < gm.GetDimension(); ++i)
    {
      state[i] = r();
      qrn[i] = (double)state[i] * BV_RES;
    }
}

/////////////////////////////////////////////////////////////////////////////

inline void LinearScrambled::Randomize()
{
  uint              i, j;
  GeneratorMatrices L(gm.GetDimension());
  
  Reset();
  for (i = 0; i < gm.GetDimension(); ++i)
    {
      L.SetRow(i, 0, BV_MAXBIT);
      for (j = 1; j < BV_BITS; ++j)
	L.SetRow(i, j, (((r() << 1) | 1) << (BV_BITS-1-j)));
    }
  gm = L * originalgm;
}

/////////////////////////////////////////////////////////////////////////////

inline Scrambled &Scrambled::operator++()
{
  uint i;
  
  ++count;
  for (i = 0; i < gm.GetDimension(); ++i)
    qrn[i] = (double)data[i*n+count] * BV_RES;
  return *this;
}

inline void Scrambled::Randomize()
{
  typedef struct
  {
    bitvector bv;
    uint      pos;
  } posbitvector;
  
  uint         i, j, b, bb, pos;
  bitvector    bv, bv2, *bvptr;
  posbitvector *pbvlist, *pbvptr;
  posbitvector **binpos;
  uint         *counts;
  
  Reset();
  pbvlist = new posbitvector[2*n];
  counts = new uint[256];
  binpos = new posbitvector*[256];
  for (i = 0; i < gm.GetDimension(); ++i)
    {
      pbvptr = pbvlist;
      pbvptr->bv = state[i];
      pbvptr->pos = 0;
      for (j = 1; j < n; ++j)
	{
	  ++pbvptr;
	  for (pos = 0, bv = 1; !(j & bv); ++pos, bv <<= 1);
	  pbvptr->bv = (pbvptr-1)->bv ^ gm.GetColumn(i, pos);
	  pbvptr->pos = j;
	}
      for (b = 0; b < 4; ++b)
	{
	  for (j = 0; j < 256; ++j)
	    counts[j] = 0;
	  pbvptr = pbvlist + (b%2 * n);
	  bb = 8*b;
	  bv = (0xFF << bb);
	  for (j = 0; j < n; ++j, ++pbvptr)
	    ++counts[(pbvptr->bv & bv) >> bb];
	  binpos[0] = pbvlist + ((1-b%2) * n);
	  for (j = 0; j < 255; ++j)
	    binpos[j+1] = binpos[j] + counts[j];
	  pbvptr = pbvlist + (b%2 * n);
	  for (j = 0; j < n; ++j, ++pbvptr)
	    {
	      pos = (pbvptr->bv & bv) >> bb;
	      *(binpos[pos]) = *pbvptr;
	      ++(binpos[pos]);
	    }
	}
      pbvptr = pbvlist;
      bvptr = data + i*n;
      bv = r();
      bvptr[pbvptr->pos] = pbvptr->bv ^ bv;
      state[i] = bvptr[pbvptr->pos];
      qrn[i] = (double)state[i] * BV_RES;
      for (j = 1; j < n; ++j)
	{
	  bv2 = pbvptr->bv;
	  ++pbvptr;
	  bv2 ^= pbvptr->bv;
	  bv2 = r() & ((bitvector)(1 << ilogb((double)bv2)) - 1);
	  bv ^= bv2;
	  bvptr[pbvptr->pos] = pbvptr->bv ^ bv;
	}
    }
  delete []pbvlist;
  delete []counts;
  delete []binpos;
}

/////////////////////////////////////////////////////////////////////////////

#endif
