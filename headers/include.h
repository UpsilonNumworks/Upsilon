#include <stddef.h>

// https://android.googlesource.com/platform/system/core.git/+/master/libcutils/strlcpy.c
inline size_t strlcpy(char *dst, const char *src, size_t siz)
{
	char *d = dst;
	const char *s = src;
	size_t n = siz;
	/* Copy as many bytes as will fit */
	if (n != 0) {
		while (--n != 0) {
			if ((*d++ = *s++) == '\0')
				break;
		}
  }
	/* Not enough room in dst, add NUL and traverse rest of src */
	if (n == 0) {
		if (siz != 0)
			*d = '\0';		/* NUL-terminate dst */
		while (*s++)
			;
	}
	return(s - src - 1);	/* count does not include NUL */
}

#include <math.h>

// If using C++
#ifdef __cplusplus
	extern "C++" {
		namespace std {
			// functions
			using ::acosh;
			using ::acoshf;
			using ::acoshl;

			using ::asinh;
			using ::asinhf;
			using ::asinhl;

			using ::atanh;
			using ::atanhf;
			using ::atanhl;

			using ::cbrt;
			using ::cbrtf;
			using ::cbrtl;

			using ::copysign;
			using ::copysignf;
			using ::copysignl;

			using ::erf;
			using ::erff;
			using ::erfl;

			using ::erfc;
			using ::erfcf;
			using ::erfcl;

			using ::exp2;
			using ::exp2f;
			using ::exp2l;

			using ::expm1;
			using ::expm1f;
			using ::expm1l;

			using ::fdim;
			using ::fdimf;
			using ::fdiml;

			using ::fma;
			using ::fmaf;
			using ::fmal;

			using ::fmax;
			using ::fmaxf;
			using ::fmaxl;

			using ::fmin;
			using ::fminf;
			using ::fminl;

			using ::hypot;
			using ::hypotf;
			using ::hypotl;

			using ::ilogb;
			using ::ilogbf;
			using ::ilogbl;

			using ::lgamma;
			using ::lgammaf;
			using ::lgammal;

			using ::llrint;
			using ::llrintf;
			using ::llrintl;

			using ::llround;
			using ::llroundf;
			using ::llroundl;

			using ::log1p;
			using ::log1pf;
			using ::log1pl;

			using ::log2;
			using ::log2f;
			using ::log2l;

			using ::logb;
			using ::logbf;
			using ::logbl;

			using ::lrint;
			using ::lrintf;
			using ::lrintl;

			using ::lround;
			using ::lroundf;
			using ::lroundl;

			using ::nan;
			using ::nanf;
			using ::nanl;

			using ::nearbyint;
			using ::nearbyintf;
			using ::nearbyintl;

			using ::nextafter;
			using ::nextafterf;
			using ::nextafterl;

			using ::nexttoward;
			using ::nexttowardf;
			using ::nexttowardl;

			using ::remainder;
			using ::remainderf;
			using ::remainderl;

			using ::remquo;
			using ::remquof;
			using ::remquol;

			using ::rint;
			using ::rintf;
			using ::rintl;

			using ::round;
			using ::roundf;
			using ::roundl;

			using ::scalbln;
			using ::scalblnf;
			using ::scalblnl;

			using ::scalbn;
			using ::scalbnf;
			using ::scalbnl;

			using ::tgamma;
			using ::tgammaf;
			using ::tgammal;

			using ::trunc;
			using ::truncf;
			using ::truncl;
		}
	}
#endif
