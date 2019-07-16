#ifndef lzesp_H
#define lzesp_H
#include <vector>
#include <complex>

struct lzespolone{
	float cz_rz;
	float cz_ur;
};

typedef struct lzespolone lz;

typedef std::complex <float> CV;

#endif
