#include <iostream>
#include "Vect.h"

using namespace std;

int main()
{
	Vect v;
	v.size = 2;
	v.capacity = 2;
	v.arr = new int[v.capacity];
	v.arr[0] = 2;
	v.arr[1] = 3;
	//v.arr[2] = 4;
	int val = 5;
	cout << "size before " << v.size << endl;
	cout << "capacity before " << v.capacity << endl;
	cout << "vector: ";
	for(int i =0; i < v.size; ++i){
		cout << v.arr[i] << " ";
	}
	cout << endl;
	vect_push_back(v, val);
	cout << "capacity " << v.capacity << endl;
	cout << "size " << v.size << endl;
	cout << "vector: ";
	//cout << "capacity " << v.capacity << endl;
	for(int i =0; i < v.size; ++i){
		cout << v.arr[i] << " ";
	}

	return 0;
}