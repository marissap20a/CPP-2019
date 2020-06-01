#ifndef STACK_H
#define STACK_H

// define the Stack type
// a new stack is initially empty and has capacity 1
template<typename T>
class Stack {
	public:
		T pop();
		void push(T);
		bool isEmpty();
	private:
		T* A = new T[1];    // array for storage
		int capacity = 1;       // capacity of A
		int length = 0;
		// number of elements in A
};

template<typename T>
bool Stack<T>::isEmpty(){
	if(length == 0){
		return true;
	}
	else{
		return false;
	}
}

template<typename T>
void Stack<T>::push(T element) {
	//resizing array 
	if (length == capacity) {
		int newCapacity = capacity * 2;
		T *temp_s = new T[capacity * 2];
		
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


template<typename T>
T Stack<T>::pop() {
	if(isEmpty()==true) {
		exit(0);
	}
	if(length > 0){
		length = length-1;
		return A[length];
	}
}



#endif