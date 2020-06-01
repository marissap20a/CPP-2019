#include <iostream>
#include <string>
#include "Stack.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main() {
    Stack<string> s;
	std::string userString;
	int s_length;
	int count = 0;
	
	cin >> userString;
	if(userString[userString.size()-1] == '.'){
		s.push(userString.substr(0,userString.size()-1));
		count += 1;
	}
	else{
		s.push(userString);
		count += 1;
	}
	
	while(userString[userString.size()-1] != '.'){
		cin >> userString;
		if(userString[userString.size()-1] == '.'){
			s.push(userString.substr(0,userString.size()-1));
			count += 1;
		}
		else{
			s.push(userString);
			count += 1;
		}
		
	}
	for(int i = 0; i < count + 1; ++i){
		cout << s.pop() << " ";
	}
}
