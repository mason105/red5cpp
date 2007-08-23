
#include "Random.h"
#include "math/gmath.h"
#include "lang/System.h"
#include "lang/IllegalArgumentException.h"
#include "lang/NullPointerException.h"
using namespace goddk::math;
using namespace goddk::lang;

namespace goddk {
namespace util {

Random::Random()
: _haveNextNextGaussian(false),
  _nextNextGaussian(0),
  _seed(0)
{
  setSeed(System::currentTimeMillis());
}

Random::Random(jlong seed)
: _haveNextNextGaussian(false),
  _nextNextGaussian(0),
  _seed(0)
{
  setSeed(seed);
}

//virtual 
bool 
Random::nextBoolean()
{
  return _nextBits(1) != 0;
}


double 
Random::nextDouble()
{
  synchronized(this);
  return (( ((jlong)_nextBits(26)) << 27) + _nextBits(27)) / 
                              (double)(jlong(1) << 53);
}

float 
Random::nextFloat()
{
  return _nextBits(24) / ((float)(1 << 24));
}

double 
Random::nextGaussian()
{
	synchronized(this);
  if (_haveNextNextGaussian == true) {
    _haveNextNextGaussian = false;
    return _nextNextGaussian;
  } 
  double v1, v2, s;
  do {
    v1 = 2 * nextDouble() - 1; // between -1.0 and 1.0
    v2 = 2 * nextDouble() - 1; // between -1.0 and 1.0
    s = v1 * v1 + v2 * v2;
  } while (s >= 1);
  double norm = Math::sqrt(-2 * Math::log(s) / s);
  _nextNextGaussian = v2 * norm;
  _haveNextNextGaussian = true;
  return v1 * norm;
}

int 
Random::nextInt()
{
  return _nextBits(32);
}

int 
Random::nextInt(int n)
{
	synchronized(this);
  if (n <= 0)
    THROWEXCEPTIONPTR(NullPointerException)
  if ((n & -n) == n)  // i.e., n is a power of 2
    return (int)((n * (long)_nextBits(31)) >> 31);
  int bits, val;
  do {
    bits = _nextBits(32);
    val = bits % n;
  } while(bits - val + (n-1) < 0);
  return val;
}


jlong 
Random::nextLong()
{
	synchronized(this);
  return ((jlong)_nextBits(32) << 32) + jlong(_nextBits(32));
}

const __int64 scrampleconstant = 0x5DEECE66DLL;

int 
Random::_nextBits(int bits)
{
  if (bits < 1 || bits > 32)
    THROWEXCEPTIONPTR(NullPointerException)

  _seed = (_seed * scrampleconstant) & ((jlong(1) << 48) - 1);
  return (int) (_seed >> (48 - bits));
}

void 
Random::setSeed(jlong seed) 
{
	synchronized(this);
  _seed = (seed ^ scrampleconstant) & ((jlong(1) << 48) - 1);
  _haveNextNextGaussian = false;
}

}
} 


