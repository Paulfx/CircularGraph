#include "Graph.h"

const char* couleur_defaut = "\033[0m";
const char* VERT = "\033[0;32m";
const char* ROUGE = "\033[0;31m";
const char* MARRON = "\033[0;33m";
//const char* save = "\033[s";
//const char* restore= "\033[u";

/**
 * @file main.cpp
 * @brief Renvoie l'entier positif choisi par l'utilisateur.
 * @details Tant que l'utilisateur ne rentre pas un entier positif,
 * 			écrit le message et attends un entier positif.
 * 
 * @param[in] message : Le message à écrire à l'utilisateur.
 * @return unsigned_int : l'entier positif choisi.
 */
unsigned int getNumber(const char* message) {
	unsigned int n;
	std::cout << message;
	while (!(std::cin >> n)) {
		std::cin.clear();
		std::cin.ignore(100,'\n'); //On efface les 100 dernières lignes du buffer cin
		std::cout << "Veuillez rentrer un entier positif." << std::endl << message;
	}
	return n;
}

int main(int argc, char const *argv[])
{
	const char* couleurs [3];
	couleurs[0] = ROUGE;
	couleurs[1] = VERT;
	couleurs[2] = MARRON;

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


	//std::string choix;
	unsigned int choix = 0;
	std::string filename = "";
	std::string message; //Contient le message à écrire sous le menu
	std::string nonInit = "Choix non disponible. Le graphe n'est pas initialisé";
	bool quit = ( argc == 4 ); //Si argc == 4, on affiche pas le menu

	while (!quit) {

		//COULEURS
		if (init) {
			c1 = 2; //Gris
			c2 = 1; //VERT
			c3 = 1;
			c4 = 1;
		}
		else {
			c1 = 1;
			c2 = 0; //ROUGE
			c3 = 0;
			c4 = 0;
		}
		
		//MENU 

		std::cout << "---------- CODE COULEUR ----------" << std::endl << std::endl;
		std::cout << "\t" << VERT << "Disponible" << std::endl; 
		std::cout << "\t" << ROUGE << "Indisponible : graphe non initialisé" << std::endl;
		std::cout << "\t" << MARRON << "Indisponible" << std::endl << std::endl;
		std::cout << couleur_defaut << "-------------- MENU --------------" << std::endl << std::endl;
		std::cout << couleurs[c1] << "1. Créer le graphe à partir d'un fichier." << std::endl;
		std::cout << couleurs[c2] << "2. Afficher le graphe." << std::endl;
		std::cout << couleurs[c3] << "3. Modifier un sommet." << std::endl;
		std::cout << couleurs[c4] << "4. Recherche d'un chemin." <<  couleur_defaut << std::endl;
		std::cout << VERT << "5. Quitter." <<  couleur_defaut << std::endl;
		std::cout << message << std::endl;
		
		std::cin >> choix;
		std::cout << "\033[2J\033[H"; //On efface le terminal et on revient en haut à gauche

		if (!std::cin) { //Le choix n'est pas un entier
			message = "Choix non compris, veuillez réessayer";
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}
		else { //Le choix est un entier
			if (choix == 1) { //Création
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

			else if (choix == 2) { //Affichage
				if (init) {
					gr.affiche();
					message = "";
				}
				else message = nonInit;
			}

			else if (choix == 3) { //Modification
				if (init) {
					unsigned int sommet;
					Sommet altitude;
					std::cout << "Veuillez choisir : " << std::endl;
					sommet = getNumber("\t 1. Indice du sommet à changer : ");
					altitude = getNumber("\t 2. Son altitude : ");

					if (!gr.setTab(sommet, altitude)) message = "Erreur lors de la modification, rien n'a été modifié";
					else message = "Modification réussie.";
				}
				else message = nonInit;
			}

			else if (choix == 4) { //Recherche de chemin
				if (init) {
					int depart, arrivee;
					std::cout << "Veuillez choisir : " << std::endl;
					depart = getNumber("\t 1. Sommet de départ : ");
					arrivee = getNumber("\t 2. Sommet d'arrivée : ");

					if (!gr.chercheChemin(depart, arrivee)) message = "Aucun chemin trouvé. Cela n'est vraiment pas normal !";
					else message = ""; 
				}
				else message = nonInit;
			}

			else if (choix == 5) { //Quitter
				quit = true; //C'est fini !
			}

			else { //Non compris
				message = "Choix non compris, veuillez réessayer";
			}
		}

		std::cout << std::endl << std::endl << std::endl;

	} //Fin while

	return 0;
}