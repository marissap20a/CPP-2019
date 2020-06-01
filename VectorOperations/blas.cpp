/*
BLAS Level 1 function definitions
*/

#include "blas.h"
#include <iostream>
#include <cmath>
using std::cout;
using std::cin;
using std::endl;

int amax(const double* x, const unsigned int len) {
    double max_val = x[0];
	unsigned int max_val_pos = 0;
	int abs_val;
	unsigned int i;
	if (len == 0) {
		return -1;
	}
	
	else {
		for (i = 0; i < len ; i++) {
			abs_val = abs(x[i]);
			if (abs_val > max_val) {
				max_val = abs_val;
				max_val_pos = i;
			}
		}	
		return max_val_pos;
	}
	return 0;
}

double asum(const double* x, const unsigned int len) {
    
	double sum_val = 0;
	unsigned int i;
	double abs_val; 
	if (len == 0) {
		return 0;
	}
	else {
		for (i = 0; i < len ; ++i) {
			abs_val = abs(x[i]);
			sum_val += abs_val;
		}
		return sum_val;
	}
	
	return 0;
}

void axpy(const double a, const double* x, double* y, const unsigned int len) {
    unsigned int i;
	
	if ((a == 0) && (len == 0)) {
		return ;
	}
	
	else {
		for (i = 0; i < len ; ++i) {
			y[i] = (x[i] * a) + y[i];
			cout << "x multi in loop: " << y[i] << endl;
		}
	}
}

void copy(const double* src, double* dest, const unsigned int len) {
	for (unsigned int i = 0 ; i < len ; ++i) {
		dest[i] = src[i];
		
	}
}

double dot(const double* x, const double* y, const unsigned int len) {
    unsigned int i;
	double dot;
	double sum_prod = 0;
	
	if (len == 0) {
		return 0;
	}
	
	else {
		for (i = 0 ; i < len ; ++i) {
			dot = x[i] * y[i];
			sum_prod += dot;
		}
		return sum_prod;
	}
	
	return 0;
}

double norm2(const double* x, const unsigned int len) {
    unsigned int i;
	double sum_val_in = 0;
	
	if (len == 0) {
		return 0;
	}
	else {
		for (i = 0 ; i < len ; ++i) {
			sum_val_in += (x[i] * x[i]);
		}
		return sqrt(sum_val_in);
	}
	
	return 0;
}

void scale(const double a, double* x, const unsigned int len) {
    unsigned int i;
	
	
	if ((len == 0) && (a == 0)) {
		return ;	
	}
	else {
		for (i = 0 ; i < len ; ++i) {
			x[i] = x[i] * a;
		}
		
	}
}

void swap(double* x, double* y, const unsigned int len) {
    double dummy_var = 0;
	unsigned int i;
	for (i = 0 ; i < len ; ++i) {
		dummy_var = x[i];
		x[i] = y[i];
		y[i] = dummy_var;
	}
}