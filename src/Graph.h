#ifndef GRAPHCIRCULAIRE_H
#define GRAPHCIRCULAIRE_H

#include <functional>
/**
* @class GraphCirculaire
* @brief [brief description]
* @details [long description]
* 
*/

class GraphCirculaire {

private:

	int* tab;
	unsigned int nbCouche;
	
public:

	GraphCirculaire();

	/** 
 	* @brief Constructeur par defaut
 	*/
	GraphCirculaire(unsigned int C);

	/** 
 	* @brief Destructeur.
 	*/
 	~GraphCirculaire();

 	int voisin(unsigned int i);
};

#endif //GRAPHCIRCULAIRE_H