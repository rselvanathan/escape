/*
This class gives a unqiue key to each object depending on its name. This makes it easier to 
work out collisions between objects. This class also makes it easier to compare different game entities.

Author : Chris Child

Reference : Chris Child, 2nd Year Asteroids Project 
*/

#include "GameUtil.h"
#include "GameObjectType.h"

/* Give a hash key to each name */
unsigned long GameObjectType::HashName(char const * pTypeName)
{
	// largest prime smaller than 65536
	unsigned long BASE = 65521L;

	// NMAX is the largest n such that
	// 255n(n+1)/2 + (n+1)(BASE-1) <= 2^32-1
	unsigned long NMAX = 5552;

	#define DO1(buf, i) {s1 += tolower(buf[i]); s2 += s1;}
	#define DO2(buf, i) DO1(buf, i); DO1(buf, i+1);
	#define DO4(buf, i) DO2(buf, i); DO2(buf, i+2);
	#define DO8(buf, i) DO4(buf, i); DO4(buf, i+4);
	#define DO16(buf)   DO8(buf, 0); DO8(buf, 8);

	if (pTypeName == NULL) return NULL;

	unsigned long s1 = 0;
	unsigned long s2 = 0;

	for (size_t len = strlen(pTypeName); len > 0; ) {
		unsigned long k = (len < NMAX) ? len : NMAX;
		len -= k;
		while (k >= 16) {
			DO16(pTypeName);
			pTypeName += 16;
			k -= 16;
		}
		if (k != 0) {
			do {
				s1 += *pTypeName++;
				s2 += s1;
			} while (--k);

			s1 %= BASE;
			s2 %= BASE;
		}
	}

	return (s2 << 16) | s1;

	#undef DO1
	#undef DO2
	#undef DO4
	#undef DO8
	#undef DO16
}