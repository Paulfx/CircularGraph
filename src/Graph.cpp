#include "Graph.h"

//const int Infini = std::numeric_limits<int>::max(); Pas besoin d'infini car on teste d'abord si un élément est dans le PCD

GrapheCirculaire::GrapheCirculaire() : nbCouche(0) { tab = 0; }

GrapheCirculaire::GrapheCirculaire(unsigned int C) : nbCouche(C) { 
	l = 1 << C; //2^C
	tab = new Sommet[l]; //On laisse la première case vide (indice commence à 1)
	//Initialement, toute les altitudes sont nulles
	for (unsigned int i = 0; i<l; ++i) tab[i] = 0;
}

GrapheCirculaire::~GrapheCirculaire() { delete tab; }

bool GrapheCirculaire::loadFromFile(const char* fileName) {
	std::ifstream f("./" + std::string(fileName)); //On regarde dans le dossier actuel
	if (!f.is_open()) return false;
	//On ne modifie pas un graphe déjà crée
	if (tab != 0) return false;
	unsigned int C;
	f >> C;

	l = 1 << C; //2^C
	tab = new Sommet[l];
	Sommet tmp;
	for (unsigned int i = 1; i < l; ++i) {
		f >> tmp;
		tab[i] = tmp;
	}

	f.close();
	return true;
}

bool GrapheCirculaire::setTab(unsigned int i, const Sommet& s) {
	if (tab != 0 && i >= 1 && i < l) {
		tab[i] = s;
		return true;
	}
	else return false;
}

unsigned int GrapheCirculaire::plusProchePuissance2(unsigned int i) {
	if (i == 0) return i;
	unsigned int n = 0;
	while (i != 1) {
		i >>= 1;
		n++;
	}
	return n;
}

int GrapheCirculaire::voisin(unsigned int i, unsigned int num) {
	if (tab == 0) return -1;

	unsigned int iDepart = plusProchePuissance2(i);//Couche de i 
	iDepart = 1 << iDepart; ////2^j avec j la couche de i
	if( i >= l/2 && i < l) {
		//le sommet i est dans la dernière couche
		switch(num) {
			case 0: return iDepart+(i-1)%iDepart;
			case 1 : return iDepart+((i-iDepart)+1)%iDepart;
			case 2: return i/2;
			default : return -1;
		}
	}
	switch(num) {
		//Le sommet i n'est pas dans la dernière couche
		case 0 : return i*2;
		case 1 : return (i*2)+1;
		case 2 : {
			if (i == 1) return -1; //Le premier sommet n'a que deux voisins
			return i/2;
		}
		case 3 : return iDepart+(i-1)%iDepart;
		case 4 : return iDepart+((i-iDepart)+1)%iDepart;
		default : return -1;
	}
}

bool GrapheCirculaire::chercheChemin(unsigned int depart, unsigned int arrivee) {
	assert(depart >= 1 && depart < l);
	assert(arrivee < l && arrivee >= 1);

	typedef struct {
		bool vu; //false si on n'a jamais vu ce sommet, true sinon
		int distance;
		unsigned int pred;
	} dataSommet;
	//On stocke pour chaque sommet l'info vu, la distance depuis l'origine et son prédecesseur.
	dataSommet tabChemin[l];
	tabChemin[1] = {true, 0, 0};
	for(unsigned int i=2; i<l; ++i) {
		tabChemin[i] = {false, 0, 0};
	}

	typedef std::pair<int,unsigned int> chemin; //First : coût + estimation à la cible, Second : indice du sommet

	//Structure pour comparer deux chemins selon leur coût.
	typedef struct {
		bool operator()(const chemin& g, const chemin& d) { return g.first > d.first; }
	} CompareCout; 

	std::priority_queue<chemin,
						std::vector<chemin>,
						CompareCout> filePrioChemin;

	filePrioChemin.push(std::make_pair(0,depart)); //Initialement
	//int cout;
	unsigned int coucheArrivee = plusProchePuissance2(arrivee); //Numéro de la couche du sommet d'arrivee
	int distanceTotaleAParcourir = std::abs(tab[depart] - tab[arrivee]);

	unsigned int indice; //Indice du sommet courant
	unsigned int numVoisin; //Les numéros successifs des voisins d'un sommet
	int iVoisin; //Indice du voisin courant du sommet courant
	int distanceVoisin; //La distance du sommet courant vers le voisin courant
	int coutVoisin; //Le cout total pour aller au voisin courant
	unsigned int estimationCible;
	int diffCouche;
	
	while(!filePrioChemin.empty()) { //On a encore des chemins à essayer
		//On prend le plus "probable" en 1er
		std::tie(std::ignore, indice) = filePrioChemin.top(); //Le premier élément n'est là que pour la comparaison
		
		//cout = tabChemin[indice].distance;
		if (indice == arrivee) { //On a trouvé le chemin
			tabChemin[arrivee].vu = true;
			break;
		}
		//Sinon
		filePrioChemin.pop();
		numVoisin = 0;
		iVoisin = voisin(indice, numVoisin);
		
		while(iVoisin != -1) { //On a encore des voisins non parcourus

			distanceVoisin = std::abs(tab[indice] - tab[iVoisin]);
			coutVoisin = tabChemin[indice].distance + distanceVoisin; //Le coût du chemin est la distance connue + la distance vers le voisin

			if (!tabChemin[iVoisin].vu || coutVoisin < tabChemin[iVoisin].distance) {
				//On ajoute (ou on remplace si le chemin est meilleur) ce chemin à l'indice iVoisin
				tabChemin[iVoisin] = {true, coutVoisin, indice};
				//On l'insère dans notre structure de tri en prenant en compte l'estimation et la différence de couche
				estimationCible = std::abs(distanceTotaleAParcourir - distanceVoisin); //Distance restante à parcourir
				diffCouche = std::abs((int) (plusProchePuissance2(iVoisin) - coucheArrivee)); //Différence de couche entre le sommet et l'arrivée
				filePrioChemin.push(std::make_pair(coutVoisin + estimationCible + diffCouche, iVoisin));
			}
			iVoisin = voisin(indice, ++numVoisin);
		}
	}

	if (tabChemin[arrivee].vu) { //Donc tabChemin[arrivee].distance et .pred ont une valeur
		unsigned int sommetTmp = arrivee;
		std::string sChemin = std::to_string(sommetTmp);
		std::string tmpS;
		while (sommetTmp != depart) {
			tmpS = std::to_string(tabChemin[sommetTmp].pred) + "->";
			sChemin.insert(0,tmpS);
			sommetTmp = tabChemin[sommetTmp].pred;
		}
		//On affiche le chemin trouvé
		std::cout << "Le chemin trouvé pour aller du sommet n°" << depart << " jusqu'au sommet n°" << arrivee << " est : " <<std::endl;
		std::cout << "\n\t" << sChemin << " de coût : " << tabChemin[arrivee].distance << "." <<std::endl;
	}

	//On retourne vrai si on a trouvé un chemin, faux sinon
	return tabChemin[arrivee].vu;
}

void GrapheCirculaire::affiche() {
	unsigned int debutCouche = 1;
	unsigned int finCouche = 1;
	unsigned int compteurCouche = 1;
	while (debutCouche != l) {
		finCouche <<= 1; //Les puissances de 2
		std::cout << "Couche numéro " << compteurCouche << " :" << std::endl;
		for (unsigned int i = debutCouche; i < finCouche; ++i)
			std::cout << "\tindice = " << i << ", altitude = " << tab[i] << "." <<std::endl;
		compteurCouche++;
		debutCouche = finCouche;
	}
}