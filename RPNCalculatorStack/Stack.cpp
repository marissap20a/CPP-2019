#include <cmath> //(for NAN)
#include <iostream> //(for std::cin, cout, endl)
#include <string> //(for std::string and stod())
#include "Stack.h"

using namespace std;


void StackDouble::push( double element) {
	//resizing array 
	if (length == capacity) {
		int newCapacity = capacity * 2;
		double *temp_s = new double[capacity * 2];
		
		for (int i = 0; i < capacity; ++i){
			temp_s[i] = A[i];
		}
		delete [] A;
		capacity = newCapacity;
		A = temp_s;
	}
	A[length] = element;
	length += 1;
	//adding element	
}

bool StackDouble::isEmpty(){
	if(length == 0){
		return true;
	}
	else{
		return false;
	}
}


double StackDouble::pop() {
	if(isEmpty()==true){
		exit(1);
	}
	
	if(length > 0){
		length= length-1;
		return A[length];
	}
	return 1;
}