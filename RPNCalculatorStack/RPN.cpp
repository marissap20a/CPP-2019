
#include <cmath> //(for NAN)
#include <iostream> //(for std::cin, cout, endl)
#include <string> //(for std::string and stod())
#include "Stack.h"

using namespace std;


int main() {
	string s;
	cin >> s;
	
	
	string temp_num;
	
	double right_val;
	double left_val;
	double sol = 0;
	
	Stack r;
	
	while(s[0] != '=') {
		if(s[0] == '0' || s[0] == '1' || s[0] == '2' || s[0] == '3' || s[0] == '4' || s[0] == '5' || s[0] == '6' ||
		s[0] == '7' || s[0] == '8' || s[0] == '9' || s[0] == '+' || s[0] == '-' || s[0] == '*' ||s[0] == '/' || s[0] == ' '|| s[0] == '.' ||
		s[0] == '=') {
		}
		else {
			cout << "[ERROR] invalid operator: " << s[0] << endl;
			delete [] r.A;
			return 1;
		}
		if(s[0] == '0' || s[0] == '1' || s[0] == '2' || s[0] == '3' || s[0] == '4' || s[0] == '5' || s[0] == '6' ||
		s[0] == '7' || s[0] == '8' || s[0] == '9' || s[0] == '.' )  {
			push(r, stod(s));
		
		
		}

		
		
		
		if(s[0] == '+') {
			right_val = pop(r);
			left_val = pop(r);
			sol = right_val + left_val;
			push(r,sol);
		}
		if(s[0] == '-') {
			right_val = pop(r);
			left_val = pop(r);
			sol = left_val - right_val;
			push(r,sol);
		
		}
		if(s[0] == '*') {
			right_val = pop(r);
			left_val = pop(r);
			sol = right_val * left_val;
			push(r,sol);
		
		}
		if(s[0] == '/') {
			right_val = pop(r);
			left_val = pop(r);
			sol = left_val / right_val;
			push(r,sol);
		
		}
		cin >> s;
		
	}
	cout << pop(r) << endl;
	delete [] r.A;
	return 0;
}