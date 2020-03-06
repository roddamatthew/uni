#include <iostream>

void twofivenine(int array[], int n){
	int i;
	int twos=0;
	int fives=0;
	int nines=0;

	if(n>=1){
		for(i=0; i<n; i++){
			switch(array[i]){
				case 2:
				twos++;
				break;

				case 5:
				fives++;
				break;

				case 9:
				nines++;
				break;
			}
		}
	}

std::cout << "2:" << twos << ";5:" << fives << ";9:" << nines << ";" << std::endl;

}