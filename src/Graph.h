#ifndef GRAPHECIRCULAIRE_H
#define GRAPHECIRCULAIRE_H

#include <iostream>
//#include <limits> //std::numeric_limits
#include <queue> //std::priority_queue
#include <tuple> //std:tie
#include <cstdlib> //std::abs
#include <cassert>
#include <fstream>
#include <string>

typedef int Sommet;

/**
 * @class GrapheCirculaire
 * @brief Implémentation d'un graphe non orienté composé de couches circulaire. 
 * @details Chaque noeud possède 5 voisins, sauf :
 * 					- la dernière couche qui possède 3 voisins.
 * 					- la première couche qui possède 2 voisins.
 *			
 *			Tout chemin entre deux noeuds du graphes existe.
 */
class GrapheCirculaire {

private:
	/**
	 * @param Le tableau contenant les sommets.
	 */
	Sommet* tab;

	/**
	 * @brief Le nombre de couches du graphe.
	 */
	unsigned int nbCouche;

	/**
	 * @brief La taille du tableau = 2^nbCouche.
	 */
	unsigned int l; //2^nbCouche
	
public:

 	/** 
 	* @brief Constructeur par defaut.
 	* @details Initialise tab à 0 et le nbCouche à 0.
 	*/
	GrapheCirculaire();

	/**
	 * @brief Constructeur.
	 * @details Crée tab avec 2^C éléments.
	 * 			Initialise les altitudes à 0.
	 * 
	 * @param[in] unsigned_int C : le nombre de couches.
	 */
	GrapheCirculaire(unsigned int C);

	/** 
 	* @brief Destructeur.
 	* @details Détruit le tableau.
 	*/
 	~GrapheCirculaire();

 	/**
 	 * @brief Crée le tableau des sommets à partir d'un fichier.
 	 * @details tab ne doit pas être initialisé avant l'éxecution de la fonction.
 	 * 			Le format du fichier est le suivant :
 	 * 			
 	 * 			nbCouche\nALT1\nALT2\nALT3\n...
 	 * 			
 	 * Attention:	Si le fichier contient moins de 2^nbCouche lignes, ou que les lignes
 	 * 				sont composées de caractères autres que numériques,
 	 * 				le fonctionnement de la fonction est INDEFINI.
 	 * 
 	 * @param[in] char* fileName : le nom du fichier.
 	 * @return bool : true  -> 	si le tableau est initialisé à partir du fichier,
 	 * 				  false -> 	si le fichier n'est pas dans le dossier courant,
 	 * 				  			ou s'il ne peut être ouvert.
 	 * 
 	 * 				  		  
 	 */
 	bool loadFromFile(const char* fileName);

 	/**
 	 * @brief Modifie le tableau de sommets
 	 * @details S'il existe, la valeur à tab[i] est modifiée par s.
 	 * 
 	 * @param[in] unsigned_int i : indice dans tab
 	 * @param[in,out] Sommet s : valeur de l'altitude
 	 * 
 	 * @return bool : true si la valeur a été modifée, false sinon
 	 */
 	bool setTab(unsigned int i, const Sommet& s);

 	/**
 	 * @brief Calcule et renvoie le numéro de couche du sommet d'indice i
 	 * @details Utilise un décalage de 1 bits vers la droite successivement,
 	 * 			ie. on divise par 2 le sommet en entrée
 	 * 
 	 * @param[in] unsigned_int i : indice du sommet
 	 * @return unsigned_int : numéro de la couche (commence à 0)
 	 */	
 	unsigned int plusProchePuissance2(unsigned int i);

 	/**
 	 * @brief Retourne le num-ième voisin du sommet d'indice i
 	 * @details Vérifie la couche du sommet i et renvoie les voisins associés.
 	 * 			Renvoie -1 lorsque le sommet i n'a plus de voisins.
 	 * 
 	 * @param[in] unsigned_int i : indice du sommet.
 	 * @param[in] unsigned_int num : le numéro du voisin.
 	 *
 	 * @return int : l'indice du voisin s'il existe, -1 sinon.
 	 */
 	int voisin(unsigned int i, unsigned int num);

 	/**
 	 * @brief Recherche le meilleur chemin entre les indices départ et arrivée.
 	 * @details Implémentation de l'algorithme A*.
 	 * 			Si un chemin est trouvé, la fonction l'affiche.
 	 * 
 	 * @param[in] unsigned_int depart : indice du départ
 	 * @param[in] unsigned_int arrivee : indice de l'arrivee
 	 * 
 	 * @return bool : true si un chemin a été trouvé, false sinon
 	 */
 	bool chercheChemin(unsigned int depart, unsigned int arrivee);

 	/**
 	 * @brief Affiche le graphe.
 	 * @details L'affichage se fait couche par couche.
 	 */
 	void affiche();
};

#endif //GRAPHECIRCULAIRE_H