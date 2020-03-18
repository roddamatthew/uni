#include <iostream>
#include <string>

void print_class(std::string courses[4], std::string students[], int report_card[][4], int nstudents){
	int i=0;
	int j=0;

	std::cout << "Report Card ";

	for(i=0; i<4; i++){
		std::cout << courses[i] << " ";
	}

	std::cout << std::endl;

	for(i=0; i<nstudents; i++){
		for(j=0; j<5; j++){
			if(j==0){
				std::cout << students[i] << " ";
			}else{
				std::cout << report_card[i][j-1] << " ";
			}
		}
	std::cout << std::endl;
	}
}
