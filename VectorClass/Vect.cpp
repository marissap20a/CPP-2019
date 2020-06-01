#include "Vect.h"
#include <cstdlib>
#include <iostream>
using namespace std;





Vect vect_construct(unsigned int n, int val){
	Vect v1;
	v1.size = n;
	v1.capacity = n*2;
	v1.arr = new int[n*2];
	for(int i = 0; i < n; ++i){
		v1.arr[i] = val;	
	}
	return v1;
}

unsigned int vect_size(const Vect &v){
	return v.size;
}
unsigned int vect_capacity(const Vect &v){
	return v.capacity;
}
bool vect_empty(const Vect &v){
	if(v.size == 0){
		return true;
	}
	else{
		return false;
	}	
}

void vect_resize(Vect &v, unsigned int n){
	int copy_val = 0;
	
	if(n < v.size){
		copy_val = n; //if the desired capacity is less than the current size shrink and the new val is the shortened capacity
	}
	else{
		copy_val = v.size; // copy over all elements in array and resize;
	}
	
	int *tmp = new int[n];	// allocate memory
	
	for(int i = 0; i < copy_val; ++i){
		tmp[i] = v.arr[i];
	}
	v.size = copy_val;
	v.capacity = n;
	delete [] v.arr;
	v.arr = tmp;
}


int& vect_at(Vect &v, unsigned int idx){
	if(idx >= 0 && idx < v.size){
		v.arr[idx];
	}
	else{
		exit(1);
	}
	return v.arr[idx];
}

void vect_erase(Vect &v, unsigned int idx){
	int* temp = new int[v.size-1];
	if(idx >= 0 && idx < v.size){
		for(int i = 0; i < v.size; ++i){
			if(i < idx){
				temp[i] = v.arr[i];
			}
			else if(i == idx){
				
			}
			else{
				temp[i-1] = v.arr[i];
			}
		}
		v.size -= 1;
		delete [] v.arr;
		v.arr = temp;
		
	}
	else{
		exit(1);
	}
	
}
void vect_push_back(Vect &v, int val){
	if(v.size == v.capacity){
		vect_resize(v, v.capacity*2);
	}
	v.arr[v.size] = val;
	v.size += 1;
	
}
void vect_insert(Vect &v, unsigned int idx, int val){
	if(idx >= 0 && idx < v.size){
		if(v.size == v.capacity){
			vect_resize(v, v.capacity * 2);	
			
		}
		int* temp = new int[v.size+1];
		
		for(int i = 0; i < v.size+1; ++i){
			if(i < idx){
				temp[i] = v.arr[i];
			}
			else if(i == idx){
				temp[idx] = val;
			}
			else{
				temp[i] = v.arr[i-1];
			}
		}
		v.size += 1;
		delete [] v.arr;
		v.arr = temp;	
	}
	else{
		exit(0);
	}
	
}
void vect_clear(Vect &v){
	if(v.size > 0){
		if(v.size < 20){
			//capacity no change and dont deallocacte memory
			for(int i = v.size-1 ; i >= 0; --i){
				vect_erase(v, i);
			}
		}
		else{
			vect_resize(v, 20);
			
			for(int i = v.size-1 ; i >= 0; --i){
				vect_erase(v, i);
			}
			
			//deallocacte memory of arr
			//assign v's arr to a new array of capacity 20 and set capacity = to 20. 
			
		}
	
	}
	
}
void vect_destruct(Vect &v){
	v.arr = nullptr;
	delete [] v.arr;
	v.size = 0;
	v.capacity = 0;

}