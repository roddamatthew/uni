#include <iostream>

int maximum_sum(int *nums,int length){
	int i=0;
	int n=0;
	int k=0;
	int running_sum=0;
	int max_sum=0;
	int sum=0;

	// for(n=0;n<length;n++){
	// 	for(i=n;i<length;i++){
	// 		running_sum=running_sum+*(nums+i);
	// 	}
	
	// 	if(running_sum>max_sum){
	// 		max_sum=running_sum;
	// 	}

	// 	running_sum=0;
	// }

	for(n=0;n<length;n++){
		for(i=n;i<length;i++){
			
			for(k=n;k<i+1;k++){
				running_sum=running_sum+*(nums+k);
			}
			
			if(running_sum>max_sum){
				max_sum=running_sum;
			}

			running_sum=0;
		}

	}

	sum=max_sum;

	if(max_sum<0){
		sum=0;
	}


	return sum;
}