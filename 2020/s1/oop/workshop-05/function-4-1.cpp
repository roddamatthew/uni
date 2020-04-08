#include <iostream>

int secondSmallestSum(int *numbers,int length){
	int running_sum=0;
	int second_smallest=numbers[1];
	int smallest=numbers[1];
	int sum=0;
	int n=0;
	int k=0;
	int i=0;

	for(n=0;n<length;n++){
		for(i=n;i<length;i++){
			
			for(k=n;k<i+1;k++){
				running_sum=running_sum+*(numbers+k);
			}
			
			if(running_sum<smallest){
				smallest=running_sum;
			}else if(running_sum>smallest && running_sum<second_smallest){
				second_smallest=running_sum;
			}

			running_sum=0;
		}

	}

	sum=second_smallest;

	return sum;
}
