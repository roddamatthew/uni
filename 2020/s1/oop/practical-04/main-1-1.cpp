#include <iostream>

using namespace std;

extern void copy_2d_strings(string first[][2], string second[][2], int n);

int main(){
	int columns=2;
	string names[3][2]={"a","b","c","d","e","f"};
	string names2[3][2];

	copy_2d_strings(names,names2,columns);


	return 0;
}