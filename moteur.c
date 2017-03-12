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
			plat[i_x][i_y].x = i_x;
			plat[i_x][i_y].y = i_y;
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
		ordreJoueurs[joueur - 1][i] = liste[r] + 20 * (joueur - 1);
		//sa place dans la liste est remplacé par la celle la plus en haut du tableau
		liste[r] = liste[n];
	}
	// on ajoute le dernier terme
	ordreJoueurs[joueur - 1][19] = liste[0] + 20 * (joueur - 1);

	return 0;
}

/*!
\brief recherche si la case possède une tuile adjacente
\param x : ordonnee de la case
\param y : abscisse de la case
\return true si la case possede une tuile adjacente
\return false si la case ne possède pas de tuile adjacente
*/

bool possedeTuileAdjacente(int x, int y)
{
	historiqueCase *tab[4];
	int i;
	tab[0] = getCase(x - 1, y);
	tab[1] = getCase(x + 1, y);
	tab[2] = getCase(x, y + 1);
	tab[3] = getCase(x, y - 1);
	for (i = 0; i < 4; ++i) {
		if (getHauteurCase(*tab[i]) > 0) {
			return true;
		}
	}
	return false;
}

/*!
 * \brief permet de savoir si une superposition de couleur est valide
 * \param haut pièce du haut
 * \param bas pièce du bas
 * \return true si la superposition est valide
 * \return false si la superpostion est invalide
 */
bool estValideSuperposition(couleur haut, couleur bas)
{
	if ((haut == rouge && bas == vert) || (haut == bas && bas == rouge)) {
		return false;
	} else {
		return true;
	}
}

/*!
\brief verifie qu'un coup est valide
\param[in] coupJoueur coup du joueur
\return true si le coup est valide
\return false si le coup n'est pas possible
*/
bool estValideCoup(coup coupJoueur)
{
	historiqueCase *c1, *c2, *c3;
	int x1, x3, y1, y3;
	historiqueCase *caseCoups[3];
	if (getCasesFromCoup(coupJoueur, caseCoups) == -1) {
		return -1;
	}
	c1 = caseCoups[0];
	c2 = caseCoups[1];
	c3 = caseCoups[2];
	x1 = caseCoups[0]->x;
	x3 = caseCoups[2]->x;
	y3 = caseCoups[2]->y;
	y1 = caseCoups[0]->y;
	//verifie que toutes les case en dessous sont a la même hauteur
	if (getHauteurCase(*c1) != getHauteurCase(*c2)
	    || getHauteurCase(*c1) != getHauteurCase(*c3)) {
		return false;
	}
	//si la pièce va êtres posée au niveau zero, verifie que l'une des tuile possède un coté adjacent a une autres tuile
	if (getHauteurCase(*c1) == 0) {
		if (possedeTuileAdjacente(x1, y1) == false
		    && possedeTuileAdjacente(x3, y3) == false
		    && false == possedeTuileAdjacente(coupJoueur.xCoup,
						      coupJoueur.yCoup)) {
			return false;
		}
	} else {
		//sinon verifie que toutes les superposition sont valide
		if (!estValideSuperposition
		    (couleurPiece(coupJoueur.numeroPiece, 1),
		     (couleur) getCouleurCase(*c1))
		    ||
		    !estValideSuperposition(couleurPiece
					    (coupJoueur.numeroPiece, 2),
					    (couleur) getCouleurCase(*c2))
		    ||
		    !estValideSuperposition(couleurPiece
					    (coupJoueur.numeroPiece, 3),
					    (couleur) getCouleurCase(*c3))) {
			return false;
		}
		//verifie que la pièce va etresposé sur au moins deux autres pièces
		if (getNumeroPiece(*c1) == getNumeroPiece(*c2)
		    && getNumeroPiece(*c1) == getNumeroPiece(*c3)) {
			return false;
		}
	}
	return true;
}

/*!
\brief pose une tuile sur le plateau
\param[in] coupJoueur : coup du joueur
\return 1 si le coup a pu être effectué
\return 0 si le coup est invalide
*/
int joueCoup(coup coupJoueur)
{

	if (estValideCoup(coupJoueur) == false) {
		return 0;
	}
	historiqueCase *caseCoups[3];
	if (getCasesFromCoup(coupJoueur, caseCoups) == -1) {
		return -1;
	}

	int i;
	for (i = 0; i < 3; ++i) {
		//change la hauteur des case
		caseCoups[i]->hauteur += 1;
		//ajoute la numero de pièce a cette hauteur
		caseCoups[i]->tabEtage[getHauteurCase(*(caseCoups[i]))].
		    numeroPiece = coupJoueur.numeroPiece;
	}
	//modifie les couleurs des cases
	caseCoups[0]->tabEtage[getHauteurCase(*(caseCoups[0]))].couleurEtage =
	    PIECE[coupJoueur.numeroPiece].c1;
	caseCoups[1]->tabEtage[getHauteurCase(*(caseCoups[1]))].couleurEtage =
	    PIECE[coupJoueur.numeroPiece].c2;
	caseCoups[2]->tabEtage[getHauteurCase(*(caseCoups[2]))].couleurEtage =
	    PIECE[coupJoueur.numeroPiece].c3;
	return 1;
}

/*!
 * \brief dejoue un coup
 * \param[in] coupAnnulle : coup à annullée
 * \return 1 si tout c'est bien passé
 * \return -1 si le coup n'as pas pu etres annullé
*/

int dejoueCoup(coup coupAnnulle)
{
	historiqueCase *caseCoups[3];
	if (getCasesFromCoup(coupAnnulle, caseCoups) == -1) {
		return -1;
	}
	int i;
	//on verifie que rien n'a été posée sur la pièce
	for (i = 0; i < 3; ++i) {
		if (coupAnnulle.numeroPiece != getNumeroPiece(*(caseCoups[i]))) {
			return -2;
		}
	}
	for (i = 0; i < 3; ++i) {
		caseCoups[i]->tabEtage[getHauteurCase(*(caseCoups[i]))].
		    couleurEtage = vide;
		caseCoups[i]->tabEtage[getHauteurCase(*(caseCoups[i]))].
		    numeroPiece = 41;
		caseCoups[i]->hauteur -= 1;
	}
	return 1;

}
