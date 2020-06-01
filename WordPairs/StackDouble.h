#ifndef STACK_H
#define STACK_H

// define the Stack type
// a new stack is initially empty and has capacity 1
class StackDouble {
	public:
		double pop();
		void push(double);
		
	private:
		double* A = new double[1];    // array for storage
		int capacity = 1;       // capacity of A
		int length = 0;
		// number of elements in A
};

#endif