#include "Graph.h"

const int Infini = std::numeric_limits<int>::max();

GrapheCirculaire::GrapheCirculaire() : nbCouche(0) { tab = 0; }

GrapheCirculaire::GrapheCirculaire(unsigned int C) : nbCouche(C) { 
	l = 1 << C; //2^C
	tab = new Sommet[l]; //On laisse la première case vide (indice commence à 1)
	//Initialement, toute les altitudes sont nulles
	for (unsigned int i = 0; i<l; ++i) tab[i] = 0;
}

GrapheCirculaire::~GrapheCirculaire() { delete tab; }

bool GrapheCirculaire::loadFromFile(const char* fileName) {
	std::ifstream f("./" + std::string(fileName));
	if (!f.is_open()) return false;
	//On ne modifie pas un graphe déjà crée
	if (tab != 0) return false;
	unsigned int C;
	f >> C;

	l = 1 << C;
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
	return 1 << n;
}

int GrapheCirculaire::voisin(unsigned int i) {
	//A MODIF AVEC NOMBRE VOISINS !!
	if (tab == 0) return -1;
	static int a = -1;
	unsigned int iDepart = plusProchePuissance2(i); //2^j avec j la couche de i
	std::cout<<"---"<<iDepart<<std::endl;
	++a;
	if( i >= l/2 && i < l) {
		//le sommet i est dans la dernière couche
		switch(a) {
			case 0: return iDepart+(i-1)%iDepart;
			case 1 : return iDepart+((i-iDepart)+1)%iDepart;
			case 2: return i/2;
			default : a=-1; return -1;
		}
	} 
	switch(a) {
		case 0 : return i*2;
		case 1 : {
			if (i == 1) a=5; //Le premier sommet n'a que deux voisins
			return (i*2)+1;
		}
		case 2 : return i/2;
		case 3 : return iDepart+(i-1)%iDepart;
		case 4 : return iDepart+((i-iDepart)+1)%iDepart;
		default : a=-1; return -1;
	}
}

bool GrapheCirculaire::chercheChemin(unsigned int depart, unsigned int arrivee) {
	assert(depart >= 1 && depart < l);
	assert(arrivee < l && arrivee >= 1);

	typedef struct {
		bool vu;
		int distance;
		unsigned int pred;
	} dataSommet;

	dataSommet tabChemin[l];
	for(unsigned int i=1; i<l; ++i) {
		tabChemin[i] = {false, 0, 0};
	}

	typedef std::pair<int,unsigned int> chemin; //First : coût, Second : indice du sommet
	typedef struct {
		bool operator()(const chemin& g, const chemin& d) { return g.first > d.first; }
	} CompareCout; //On compare deux chemins selon leur coût.

	std::priority_queue<chemin,
						std::vector<chemin>,
						CompareCout> filePrioChemin;
	filePrioChemin.push(std::make_pair(0,depart)); //Initialement
	bool trouve;
	int cout;
	unsigned int indice;
	int iVoisin; //Contient les indices des voisins du sommet 'indice'
	int nvCout;
	while(!filePrioChemin.empty()) {
		//On a encore des chemins à essayer
		//On prend le plus "probable" en 1er
		std::tie(cout, indice) = filePrioChemin.top();
		std::cout<<indice<<std::endl;
		if (indice == arrivee) {
			trouve = true;
			break;//On a trouvé le chemin
		}
		//Sinon
		filePrioChemin.pop();
		iVoisin = voisin(indice);
		while(iVoisin != -1) {
			//On a encore des voisins non parcourus
			nvCout = cout + std::abs(tab[indice] - tab[iVoisin]) + estimation(iVoisin, arrivee); //TODO diff couche
			if (!tabChemin[iVoisin].vu || nvCout < tabChemin[iVoisin].distance) {
				//On ajoute (ou on remplace) ce chemin à l'indice iVoisin
				tabChemin[iVoisin] = {true, nvCout, indice};
				filePrioChemin.push(std::make_pair(nvCout, iVoisin));
			}
			iVoisin = voisin(indice);
		}
	}

	if (trouve) {
		unsigned int tmp = arrivee;
		std::string sr= std::to_string(tmp);
		std::string tmpS;
		while (tmp != depart) {
			tmpS = std::to_string(tabChemin[tmp].pred) + "->";
			sr.insert(0,tmpS);
			tmp = tabChemin[tmp].pred;

		}

		std::cout<<sr<<std::endl;

	}

	return trouve;
}

unsigned int GrapheCirculaire::estimation(unsigned int depart, unsigned int arrivee) {
	assert(depart >= 1 && depart < l);
	assert(arrivee < l && arrivee >= 1);
	return std::abs(tab[depart] - tab[arrivee]);
}

void GrapheCirculaire::affiche() {
	unsigned int debut = 1;
	unsigned int fin = 1;
	unsigned int compteurCouche = 1;
	while (debut != l) {
		fin = fin << 1; //Les puissances de 2
		std::cout << "Couche numéro " << compteurCouche << " :" << std::endl;
		for (unsigned int i = debut; i < fin; ++i) {
			std::cout << "\t" << "indice = " << i <<", altitude = " << tab[i] << ".";
			std::cout << std::endl;
		}
		compteurCouche++;
		debut = fin;
	}
}