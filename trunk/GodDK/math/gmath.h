#pragma	  once
#include <math.h>
#include <time.h>
#include <stdlib.h>

#ifdef min
#  undef min
#endif
#ifdef max
#  undef max
#endif
#ifdef abs
#  undef abs
#endif

 

namespace goddk {
	namespace math {
		class Math
		{
			static bool _rand_inited;
			public :
			template <class T> static T abs(T t) { return (t < 0) ? (t * -1) : (t); }
			template <class T> static T min(T t1, T t2) { return (t1 < t2) ? t1 : t2; }
			template <class T> static T max(T t1, T t2) { return (t1 > t2) ? t1 : t2; }

			static double acos(double a) { return ::acos(a); }
			static double atan(double a) { return ::atan(a); }
			static double atan2(double a, double b) { return ::atan2(a, b); }
			static double ceil(double a) { return ::ceil(a); }
			static double cos(double a) { return ::cos(a); }
			static double exp(double a) { return ::exp(a); }
			static double floor(double a) { return ::floor(a); }
			static double log(double a) { return ::log(a); }
			static double pow(double a, double b) { return ::pow(a, b); }
			static double random() 
			{
				if (_rand_inited == false) {
				srand((unsigned)time(NULL));
				_rand_inited = true;
				}
				double erg = double(rand()) / double(RAND_MAX);
				return erg;
			}

			static int round(float a) 
			{
				return (int)floor(a + 0.5f);
			}
			static int round(double a) 
			{
				return (int)floor(a + 0.5f);
			}
			static double sin(double a) { return ::sin(a); }
			static double sqrt(double a) {  return ::sqrt(a);  }
			static double tan(double a) { return ::tan(a);  }
			static double toDegrees(double angrad) { return angrad / 0.017453292519943295; }
			static double toRadians(double angdeg) { return angdeg * 0.017453292519943295; }	
		};
	}
}