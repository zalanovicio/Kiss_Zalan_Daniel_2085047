#include <math.h>
#include <stdlib.h>

double function(double x) {
	return pow((x - 3), 2);
}

double functionanalyticderivative(double x) {
	return (2 * (x - 3));
}

double functionapproximated(double x) {
	double h = pow(10, -8);
	return ((function(x + h) - function(x)) / (h));
}