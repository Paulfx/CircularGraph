#ifndef GRAPHECIRCULAIRE_H
#define GRAPHECIRCULAIRE_H

#include <iostream>
#include <limits> //std::numeric_limits
#include <queue> //std::priority_queue
#include <tuple> //std:tie
#include <cstdlib> //std::abs
#include <cassert>
#include <fstream>
#include <string>

typedef int Sommet;

class GrapheCirculaire {

private:

	Sommet* tab;
	unsigned int l; //2^nbCouche
	unsigned int nbCouche;
	
public:

	GrapheCirculaire();

	/** 
 	* @brief Constructeur par defaut
 	*/
	GrapheCirculaire(unsigned int C);

	/** 
 	* @brief Destructeur.
 	*/
 	~GrapheCirculaire();

 	bool loadFromFile(const char* fileName);

 	bool setTab(unsigned int i, const Sommet& s);

 	unsigned int plusProchePuissance2(unsigned int i);

 	int voisin(unsigned int i);

 	bool chercheChemin(unsigned int depart, unsigned int arrivee);

 	unsigned int estimation(unsigned int depart, unsigned int arrivee);

 	void affiche();
};

#endif //GRAPHECIRCULAIRE_H