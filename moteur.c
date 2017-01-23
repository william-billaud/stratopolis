/*!
* \file moteur.c.c
* \brief fichier contenant les fonction utils au moteur du jeu
* \author billaud
* \author hipault
* \date 22/01/17
*/

#include "moteur.h"

/**\var variable global contenant le plateau*/
extern PLATEAU plat;
/**\var tableau contenant l'ordre des pièces des joueurs*/
extern ORDREPIECE ordreJoueurs[2];
/*!
 * \brief initialise le plateau (pose la pièce initiale)
 * \return 0 si tout c'est bien passé
 * \return -1 si un problème a eu lieu
 */
int initPlateau(void)
{
	int i_x;
	    /**<\var index des abscisse*/
	int i_y;
	    /**<\var indes des ordonées*/

	for (i_x = 0; i_x < TAILLEMAX; ++i_x) {
		for (i_y = 0; i_y < TAILLEMAX; ++i_y) {
			setCaseAZero(&(plat[i_x][i_y]));
		}
	}
	//pose la pièce de depart (pièce numero 0)
	plat[80][80].hauteur = 1;
	plat[80][80].tabEtage[1].couleurEtage = vert;
	plat[80][80].tabEtage[1].numeroPiece = 0;
	plat[81][80].hauteur = 1;
	plat[81][80].tabEtage[1].couleurEtage = rouge;
	plat[81][80].tabEtage[1].numeroPiece = 0;
	return 0;
}

/*!
 * \brief choisis le joueur qui commenceras
 * \return 1 si le joueur 1 commenceras
 * \return 2 si le joueur 2 commenceras
 */
int choisisJoueur(void)
{
	/* recupère le timestamp actuelle et le stock dans a) */
	unsigned int a = (unsigned int)time(NULL);
					    /**<\var seed recupere a partir du timestamp*/
	//defini la seed du lancer aléatoire
	srand(a);
	//effectue le lancer aléatoire et redui les possibilité à 1 ou 2
	return rand() % 2 + 1;
}

/*!
 * \brief initialise l'ordre des pièces dans un tableau
 * \param joueur numero du joueur
 * \return 0 si la fonctions n'a pas eu de problème pour s'effectuer
 * \return -1 si il y a eu une erreur
 */
int initOrdrePieces(int joueur)
{
	int i;
	unsigned int a;
		   /**<\var seed pour le rand()*/
	int n;
	  /**<\var nombre de pièces à tirer restantes*/
	int r;
	  /**<\var resultat du tirage aléatoire*/
	if (joueur != 1 && joueur != 2) {
		return -1;
	}
	int liste[20];
	for (i = 0; i < 20; ++i) {
		liste[i] = i + 1;
	}
	/* recupère le timestamp actuelle et le stock dans a) */
	a = (unsigned int)time(NULL);
			       /**<\var seed recupere a partir du timestamp*/
	//defini la seed du lancer aléatoire
	srand(a + 100 * joueur);
	for (i = 0; i < 19; ++i) {
		n = 20 - i - 1;
		//tirage d'une valeur aléatoire comprise entre 0 et n (nombre de pièce à tirer restante
		r = rand() % (n);
		//la pièce tirée est ajouté à la liste
		ordreJoueurs[joueur - 1][i] = liste[r];
		//sa place dans la liste est remplacé par la celle la plus en haut du tableau
		liste[r] = liste[n];
	}
	// on ajoute le dernier terme
	ordreJoueurs[joueur - 1][19] = liste[0];

	return 0;
}
