#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float mulInverse(float a);

// aufgabe1/heron <floats>[]
int main(int argc, const char *argv[]) {
	for (int i = 1; i < argc; ++i) {
		float a = strtof(argv[i], NULL);
		
		float x = mulInverse(a);
		printf("a: %f, x: %f, a*x: %f\n", a, x, a * x);
	}
}

float mulInverse(float a){
	// Required Accuracy Bounds
	const double EPS1M24 = 1.0f - pow(2, -24);
	const double EPS1P24 = 1.0f + pow(2, -24);

	float x = 1.0f;
	float p;
	
	while (1) {
		p = a * x;
		if (p < 0.5f) {
			x *= 2.0f;
		} else if (p > 1.5f) {
			x *= 0.5f;
		} else {
			break;
		}
	}
	
	// refinement loop
	while (1) {
		p = a * x;
		if (p < EPS1M24 || p > EPS1P24) {
			x *= 2.0f - p;
		} else {
			break;
		}
	}
	
	return x;
}