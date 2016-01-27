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

void dtlz6(int M, const float * X, float *objs) {
	int k = 10;
	int xDim = k + M - 1;

	float g = 0.0;
	for (int i = xDim - k; i < xDim; i++) {
		g += pow(X[i], (float)0.1);
	}
	float t = M_PI / (4.0*(1.0 + g));

	float *theta = (float *)malloc((M - 1)*sizeof(float));
	theta[0] = X[0] * M_PI / 2;
	theta[1] = X[1] * M_PI / 2;
	for (int i = 2; i < (M - 1); i++) {
		theta[i] = t*(1.0 + 2.0*g*X[i])*M_PI / 2;
	}
	for (int i = 0; i < M; i++) {
		objs[i] = 1.0 + g;
	}
	for (int i = 0; i < M; i++){
		for (int j = 0; j < M - (i + 1); j++) {
			objs[i] *= cos(theta[j]);
		}
		if (i != 0){
			int aux = M - (i + 1);
			objs[i] *= sin(theta[aux]);
		}
	}
	free(theta);
}

void dtlz5(int M, const float * X, float *objs) {
	int k = 10;
	int xDim = k + M - 1;

	float g = 0.0;
	for (int i = xDim - k; i < xDim; i++) {
		g += (X[i] - 0.5)*(X[i] - 0.5);
	}
	float t = M_PI / (4.0*(1.0 + g));

	float *theta = (float *)malloc((M - 1)*sizeof(float));
	theta[0] = X[0] * M_PI / 2;
	theta[1] = X[1] * M_PI / 2;
	for (int i = 2; i < (M - 1); i++) {
		theta[i] = t*(1.0 + 2.0*g*X[i])*M_PI / 2;
	}
	for (int i = 0; i < M; i++) {
		objs[i] = 1.0 + g;
	}
	for (int i = 0; i < M; i++){
		for (int j = 0; j < M - (i + 1); j++) {
			objs[i] *= cos(theta[j]);
		}
		if (i != 0){
			int aux = M - (i + 1);
			objs[i] *= sin(theta[aux]);
		}
	}
	free(theta);
}

void dtlz4(int M, const float * X, float *objs) {
	int k = 10;
	int xDim = k + M - 1;
	float alpha = 100.0;
	float g = 0.0;
	for (int i = xDim - k; i < xDim; i++)
		g += (X[i] - 0.5)*(X[i] - 0.5);

	for (int i = 0; i < M; i++)
		objs[i] = 1.0 + g;

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M - (i + 1); j++)
			objs[i] *= cos(pow(X[j], alpha)*(M_PI / 2.0));
		if (i != 0){
			int aux = M - (i + 1);
			objs[i] *= sin(pow(X[aux], alpha)*(M_PI / 2.0));
		}
	}
}

void dtlz3(int M, const float * X, float *objs) {
	int k = 10;
	int xDim = k + M - 1;
	float g = 0.0;
	for (int i = xDim - k; i < xDim; i++) {
		g += (X[i] - 0.5)*(X[i] - 0.5) - cos(20.0 * M_PI * (X[i] - 0.5));
	}

	g = 100.0 * (k + g);
	for (int i = 0; i < M; i++) {
		objs[i] = 1.0 + g;
	}
	for (int i = 0; i < M; i++){
		for (int j = 0; j < M - (i + 1); j++)
			objs[i] *= cos(X[j] * 0.5*M_PI);
		if (i != 0){
			int aux = M - (i + 1);
			objs[i] *= sin(X[aux] * 0.5*M_PI);
		}
	}
}

void dtlz2(int M, const float * X, float *objs) {
	int k = 10;
	int xDim = k + M - 1;
	float g = 0.0;
	for (int i = xDim - k; i < xDim; i++) {
		g += (X[i] - 0.5)*(X[i] - 0.5);
	}
	for (int i = 0; i < M; i++)
		objs[i] = 1.0 + g;

	for (int i = 0; i < M; i++){
		for (int j = 0; j < M - (i + 1); j++)
			objs[i] *= cos(X[j] * 0.5*M_PI);
		if (i != 0){
			int aux = M - (i + 1);
			objs[i] *= sin(X[aux] * 0.5*M_PI);
		}
	}
}

void dtlz1(int M, const float * X, float *objs) {
	int k = 5;
	int xDim = k + M - 1;
	float g = 0.0;
	for (int i = xDim - k; i < xDim; i++)
		g += (X[i] - 0.5)*(X[i] - 0.5) - cos(20.0 * M_PI * (X[i] - 0.5));

	g = 100 * (k + g);
	for (int i = 0; i < M; i++)
		objs[i] = (1.0 + g) * 0.5;

	for (int i = 0; i < M; i++){
		for (int j = 0; j < M - (i + 1); j++)
			objs[i] *= X[j];
		if (i != 0){
			int aux = M - (i + 1);
			objs[i] *= 1 - X[aux];
		}
	}
}