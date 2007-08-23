
#ifndef acdk_util_Random_h
#define acdk_util_Random_h

#include "lang/String.h"
#include "lang/IllegalArgumentException.h"
using namespace goddk::lang;

namespace goddk {
namespace util {


	class  Random:
			public virtual Object
	{	
	public:
		Random();
		Random(jlong seed);
		virtual bool nextBoolean();
		double nextDouble();
		float nextFloat();
		double nextGaussian();
		int nextInt();
		int nextInt(int n);
		jlong nextLong();
		void setSeed(jlong seed) ;
		protected:
		int _nextBits(int bits);
	private:
		bool _haveNextNextGaussian;
		double _nextNextGaussian;
		__int64 _seed;
	};
	typedef CSmartPtr<Random>		RandomPtr;

}
}

#endif 

