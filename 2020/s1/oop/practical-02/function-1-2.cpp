#include <iostream>

int identity(int array[10][10]){
	int identity_counter=0;
	int zero_entry=0;
	int identity=0;

	int i=0;
	int j=0;

	for(i=0; i<10; i++){
		for(j=0; j<10; j++){
			if(i==j){
				if(array[i][j]==1){
					identity_counter++;
				}
			}else{
				if(array[i][j]==0){
					zero_entry++;
				}
			}

		}
	}

	if(zero_entry==90 && identity_counter==10){
		identity=1;
	}

	return identity;

}