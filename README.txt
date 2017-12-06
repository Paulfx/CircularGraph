Auteur : 			Lafoix Paul
numéro étudiant : 	p1611978

---------- Utilisation du programme ----------

I) Compilation : via make

	Crée un dossier obj pour contenir les .o

II) Documentation : 

	Un fichier Doxyfile est fourni au même endroit que le README.
	Il permet de générer de la documentation sous forme HTML.

Utilisation :	Lancez la commande "doxygen Doxyfile"

Cette commande crée un dossier html à la racine du projet. La documentation 
de la classe est accessible à partir de classGraphCirculaire.html

II) Exécution

	1) Ligne de commande

			La commande "./exec.out filename depart arrivee" permet d'ouvrir le fichier et de créer 
			le graphe correspondant, puis de lancer une recherche entre le sommet départ et arrivée.

		N'affiche pas le menu.

	2) Ligne de commande + menu

			La commande "./exec.out filename" crée le graphe correspondant au fichier.
			Ensuite, le menu est affiché.


	3) Menu

			Lancez simplement la commande "./exec.out".
			Ouvre le menu.


Remarque : 	Le format du fichier est le suivant :

						nbCouche\nALT1\nALT2\nALT3\n...

			Le fichier "./g1.txt" en est un exemple.