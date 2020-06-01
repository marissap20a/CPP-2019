#include <iostream>
#include "Node.h"
#include "DoublyLinkedList.h"

using namespace std;

int main()
{	
	DoublyLinkedList<int> dll;
	cout << dll << endl;
	
	cout << dll << endl;
	
	dll.push_back(4);
	dll.push_back(5);
	dll.push_back(3);
	dll.insert(19,2);
	cout << dll << endl;
	
	
	/*
	dll.pop_front();
	cout << dll << endl;
	dll.push_back(7);
	cout << dll << endl;
	dll.pop_front();
	cout << dll << endl;
	*/
	/*
	dll.push_back(8);
	cout << dll << endl;
	dll.push_back(9);
	cout << dll << endl;
	dll.push_back(10);
	cout << dll << endl;
	dll.erase(2);
	//dll.pop_front();
	cout << dll << endl;
	*/
	
	// t.DoublyLinkedList(int 1);
	// t.DoublyLinkedList(int 2);
	// t.push_back(int i=7);
    return 0;
}