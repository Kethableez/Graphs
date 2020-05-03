#include <iostream>

#include "Driver.h"

int main(){
	int Vert_Tab[5] = { 5,25,50,75,100 };
	double Dens_Tab[4] = { 0.25,0.5,0.75,1.00 };
	int loop = 100;

	std::ofstream file("Times.txt");
	
	if (!file.is_open()) {

		std::cerr << "output not open" << std::endl;
		return 1;
	}

	file << Driver<G_List>(Vert_Tab, Dens_Tab, loop); 
	std::cout << "LIST DONE\n" << std::endl;
	std::cout << " ";
	
	file << Driver<G_Matrix>(Vert_Tab, Dens_Tab, loop);
	std::cout << "MATRIX DONE" << std::endl;

	file.close();
	return 0;
}