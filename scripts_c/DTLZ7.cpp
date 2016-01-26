#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define M_PI       3.14159265358979323846

void dtlz7(int M, const float * X, float *objs) {
	int k = 20;
	int xDim = k + M - 1;

	float xm = 0.0;
	for (int i = M - 1; i < xDim; i++) {
		xm += X[i];
	}
	float g = 0.0;
	g = 1 + (9.0 / k)*xm;
	for (int i = 0; i < M - 1; i++) {
		objs[i] = X[i];
	}
	float h = 0.0;
	for (int i = 0; i < M - 1; i++) {
		h += (objs[i] / (1 + g))*(1 + sin(3 * M_PI*objs[i]));
	}
	h = M - h;
	objs[M - 1] = (1 + g)*h;
}