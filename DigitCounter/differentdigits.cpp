#include <iostream>
#include "functions.h"
using namespace std;
int k;
int DigitOccurences;
int l;
int digit;
int repeatNumCount = 0; 
int validNums=0;
int main() {
    int a , b;
	cout << "Enter numbers a <= b: ";
	cin >> a >> b;
	
	if ( (a <= 0) || (a > 10000) || (b <= 0) || (b >10000) || (a > b)) {
		cout << "Invalid input" << endl;
	}
	else  {
		for (l = a; l <= b; ++l) {
			for (k = 0; k < 10; ++k) {
				DigitOccurences = countDigitOccurrences(l, k);
				if (DigitOccurences >= 2) {
					repeatNumCount +=1;
					break;
				}
			}	
		validNums += 1;
		}
		cout << "There are " << (b+1-a)-repeatNumCount << " valid numbers between ";
		cout << a << " and " << b << endl; 	
	}
	return 0;
}
