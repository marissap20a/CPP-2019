#include <iostream>
#include "functions.h"
using namespace std;

int zerocount = 0;
int onecount = 0;
int twocount = 0;
int threecount = 0;
int fourcount = 0;
int fivecount = 0;
int sixcount = 0;
int sevencount = 0;
int eightcount = 0;
int ninecount = 0;
int digitplace;
int valdisplay;


int countDigitOccurrences(int n, int digit) {
   
	int digitcount = 0;
	int digitobtain;
	int constantval = n;
	
	while (n > 0) {
		digitobtain = n % 10;
		//cout << "digit obtain: " << digitobtain << endl;
		n /= 10;
		if (digitobtain == digit){
			digitcount += 1;
		}
	}
	
	//cout << "the number of " << digit <<" in the number " << constantval << " is: " << digitcount << endl;
	return digitcount;
	
	
	
	
	
}
