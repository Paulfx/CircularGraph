#include "Graph.h"
#include <iostream>



GraphCirculaire::GraphCirculaire() : nbCouche(0) { tab = 0; }
GraphCirculaire::GraphCirculaire(unsigned int C) : nbCouche(C) { tab = new int[C]; }
GraphCirculaire::~GraphCirculaire() { delete tab; }

int GraphCirculaire::voisin(unsigned int i) {

	//std::cout << "\033[34;1m\n";
	static int a = 0;

	switch(a) {
		case 0 : std::cout<<"Initial"<<std::endl; break;
		case 1 : std::cout<<"1"<<std::endl; break;
		case 2 : std::cout<<"2"<<std::endl; break;
		default : std::cout<<"fini"<<std::endl; a=-1; break;
	}

	++a;

	return 0;
}
