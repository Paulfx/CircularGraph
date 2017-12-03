#include "Graph.h"
#include <iostream>
#include <string>
#include <cstdio> //getchar()
#include <cstdlib> //atoi

int main(int argc, char const *argv[])
{
	
	/*GrapheCirculaire test(4);

	//std::function<void()> a = test.iterateurVoisin(1,1);


	for(unsigned int i=1; i<16; ++i) test.setTab(i, 1);

	test.chercheChemin(12, 1);

	test.affiche();


	*/

	std::string couleur_defaut = "\033[0m";

	std::string clLigne = "\033[K"; //Efface les char du curseur à la fin de ligne

	std::string vert = "\033[0;32m";
	std::string rouge = "\033[0;31m";
	std::string marron = "\033[0;33m";
	std::string couleurs [3];
	couleurs [0] = rouge;
	couleurs [1] = vert;
	couleurs [2] = marron;

	GrapheCirculaire gr;
	bool init = false; //Etat du graphe

	unsigned int c1=0, c2=0, c3=0, c4=0;

	if (argc >= 2) {
		if (!gr.loadFromFile(argv[1])) {
			std::cout << "Erreur dans la lecture du fichier. Le graphe n'a pas été sauvegardé."; 
			std::cout << std::endl;
			//Cas non plein ?
		}
		else init = true;
		if (init && argc == 4) {
			gr.chercheChemin(atoi(argv[2]), atoi(argv[3]));
		}
	}


	std::string choix;
	std::string filename;
	std::string message;
	std::string nonInit = "Choix non disponible. Le graphe n'est pas initialisé";
	while (1) {
		//COULEURS

		if (init) {
			c1 = 2; //Gris
			c2 = 1; //Vert
			c3 = 1;
			c4 = 1;
		}
		else {
			c1 = 1;
			c2 = 0; //Rouge
			c3 = 0;
			c4 = 0;
		}
		
		//MENU 

		std::cout << " Code couleur : " << std::endl;
		std::cout << "\t" << vert << "Disponible" << std::endl; 
		std::cout << "\t" << rouge << "Indisponible : graphe non initialisé" << std::endl;
		std::cout << "\t" << marron << "Indisponible" << std::endl << std::endl;
		std::cout << couleur_defaut << "----------- MENU -----------" << std::endl << std::endl;
		std::cout << couleurs[c1] << "1. Créer le graphe à partir d'un fichier." << std::endl;
		std::cout << couleurs[c2] << "2. Afficher le graphe." << std::endl;
		std::cout << couleurs[c3] << "3. Modifier un sommet." << std::endl;
		std::cout << couleurs[c4] << "4. Recherche d'un chemin." <<  couleur_defaut << std::endl;
		std::cout << vert << "5. Quitter." <<  couleur_defaut << std::endl;
		std::cout << message << std::endl;
		
		std::cin >> choix;

		//Si choix est un entier, on peut utiliser std::stoi
		if (choix.find_first_not_of( "0123456789" ) == std::string::npos) {

			if (std::stoi(choix) == 1) { //Création
				if (!init) {
					std::cout << "Entrez le nom du fichier : ";
					std::cin  >> filename;
					if (!gr.loadFromFile(filename.c_str())) message = "Erreur de lecture du fichier";
					else {
						message = "Création du graphe réussie.";
						init = true;
					}
				}
				else message = "Choix non disponible. Le graphe est déjà initialisé";
			}

			else if (std::stoi(choix) == 2) { //Affichage
				if (init) {
					gr.affiche();
					message = "";
					std::cout << "Appuyez sur entrée pour continuer...";
					std::cin.get();
				}
				else message = nonInit;
			}

			else if (std::stoi(choix) == 3) { //Modification
				if (init) {
					int sommet;
					Sommet altitude;
					std::cout << "Veuillez choisir : " << std::endl;
					std::cout << "Indice du sommet à changer : ";
					std::cin >> sommet;
					std::cout << "Son altitude : ";
					std::cin >> altitude;

					if (!gr.setTab(sommet, altitude)) message = "Erreur lors de la modification, rien n'a été modifié";
					else message = "Modification réussie.";
				}
				else message = nonInit;
			}

			else if (std::stoi(choix) == 4) { //Recherche de chemin
				if (init) {
					int depart, arrivee;
					std::cout << "Veuillez choisir : " << std::endl;
					std::cout << "Sommet de départ : ";
					std::cin >> depart;
					std::cout << "Sommet d'arrivée' : ";
					std::cin >> arrivee;

					if (!gr.chercheChemin(depart, arrivee)) message = "Aucun chemin trouvé. Cela n'est vraiment pas normal !";
					else message = ""; 
				}
				else message = nonInit;
			}

			else if (std::stoi(choix) == 5) {
				break; //C'est fini !
			}

			else {
				message = "Choix non compris, veuillez réessayer";
			}
		}
		else message = "Choix non compris, veuillez réessayer";

		std::cout << std::endl << std::endl << std::endl << std::endl;

	} //Fin while

	return 0;
}