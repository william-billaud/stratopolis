/*!
* \file outils.c
* \brief fichier contenant les outils utils à tous les autres modules
* \author billaud
* \author hipault
* \date 22/01/17
*/

#include "outils.h"

extern PLATEAU plat;
/**< variable global contenant le plateau*/

extern pieces PIECE[42];

/*!
\brief fonction permettant de recuperer un pointeur vers un case
\param[in] x : abscisse de la case
\param[in] y : ordonée de la case
\return NULL si la case n'est pas disponible
\return historiqueCase contenant les informations de la case
*/
historiqueCase *getCase(int x, int y)
{
	//verifie que les coordonnées demandées sont dans le tableau
	if (x < 0 || y < 0 || x > TAILLEMAX || y > TAILLEMAX) {
		//si non attribue -1 a la hauteur
		return NULL;

	} else {
		return &plat[x][y];
	}

}

/*!
\brief retourne la hauteur d'une case
\param[in] c case dont la hauteur est demandé
\return hauteur de la case, -1 en case d'erreur
*/
int getHauteurCase(historiqueCase * c)
{
	int i;
	if (c == NULL) {
		i = -1;
	} else {
		i = c->hauteur;
		if (i < 0 || i > 19) {
			i = -1;
		}
	}
	return i;
}

/*!
\brief retourne la couleur d'une case
\param[in] c  case dont la couleur est demandé
\return couleur de la case
\return -1 en case d'erreur
*/
int getCouleurCase(historiqueCase * c)
{

	if (getHauteurCase(c) == -1) {
		return -1;
	} else {
		return c->tabEtage[c->hauteur].couleurEtage;
	}
}

/*!
 * \brief initialise tout les paramètre d'une case a 0
 * \param c pointeur vers une case
 * \return 0
 */
int setCaseAZero(historiqueCase * c)
{
	int i;
	c->hauteur = 0;
	for (i = 0; i < 20; i++) {
		c->tabEtage[i].couleurEtage = vide;
		c->tabEtage[i].numeroPiece = 41;
	}
	return 0;
}

/*!
 * \brief fonction permettant de récuperer le numero de la pièce en haut d'une case
 * \param c case dont nous voulons récuperer le numero de la pièce
 * \return -2 : si la hauteur de la case est incorecte
 * \return -1 : si le numero de la case est incorecte
 * \return 41 si la case ne possède pas de pièce
 */
int getNumeroPiece(historiqueCase * c)
{
	int h = getHauteurCase(c);
	int numero;
	if (h == -1) {
		return -2;
	}
	numero = c->tabEtage[h].numeroPiece;
	if ((numero > 40 && !(h == 0 && numero == 41))
	    || (h == 0 && numero != 41)) {
		return -1;
	}
	return numero;
}

/**
 * \brief verifie si une valeur est present dans un tableau 1D d'entier
 * \param array tableau dans lequel il faut chercher la valeur
 * \param h taille du tableau
 * \param valeur valeur a chercher
 * \return false si la valeur est absent
 * \return true si la valeur est presente
 */
bool inArrayIny(int *array, unsigned int h, int valeur)
{
	int i;
	for (i = 0; i < (int)h; ++i) {
		if (*(array + i) == valeur) {
			return true;
		}

	}
	return false;
}

/*!
 * \brief retourne la couleur d'une pièce
 * \param numeroPiece numero de la pièce
 * \param numeroTuile numero de la tuile sur la pièce ( 1, 2 ou 3)
 * \return la couleur correspondant au numero de la pièce
 * \return neutre en cas d'erreur
 */
couleur couleurPiece(int numeroPiece, int numeroTuile)
{

	if (numeroPiece < 0 || numeroPiece > 41) {
		return neutre;

	} else {
		switch (numeroTuile) {
		case 1:
			return PIECE[numeroPiece].c1;
		case 2:
			return PIECE[numeroPiece].c2;
		case 3:
			return PIECE[numeroPiece].c3;
		default:
			return neutre;

		}
	}
}

/*!
 * \brief initalise les pièces du jeu dans un tableau
 * \return 0 si tout c'est bien passé
 */
int initPiece(void)
{
	int i;
	couleur c1, c2, c3;
	for (i = 1; i <= 10; ++i) {
		c1 = vert;
		c2 = vert;
		c3 = vert;
		switch (i) {
		case 1:
			break;
		case 2:
			c3 = rouge;
			break;
		case 3:
			c2 = rouge;
			break;
		case 4:
			c1 = rouge;
			break;
		case 5:
			c3 = neutre;
			break;
		case 6:
			c2 = neutre;
			break;
		case 7:
			c1 = neutre;
			break;
		case 8:
			c1 = neutre;
			c2 = neutre;
			break;
		case 9:
			c2 = neutre;
			c3 = neutre;
			break;
		case 10:
			c1 = neutre;
			c3 = neutre;
			break;
		default:
			c1 = neutre;
			c2 = neutre;
			c3 = neutre;
			break;
		}
		PIECE[i].c1 = c1;
		PIECE[i].c2 = c2;
		PIECE[i].c3 = c3;
		PIECE[i].numeroPiece = (unsigned char)i;
		PIECE[i + 10].c1 = c1;
		PIECE[i + 10].c2 = c2;
		PIECE[i + 10].c3 = c3;
		PIECE[i + 10].numeroPiece = (unsigned char)(i + 10);
		if (c1 == vert) {
			c1 = rouge;
		} else if (c1 == rouge) {
			c1 = vert;
		}
		if (c2 == vert) {
			c2 = rouge;
		} else if (c2 == rouge) {
			c2 = vert;
		}
		if (c3 == vert) {
			c3 = rouge;
		} else if (c3 == rouge) {
			c3 = vert;
		}
		PIECE[i + 20].c1 = c1;
		PIECE[i + 20].c2 = c2;
		PIECE[i + 20].c3 = c3;
		PIECE[i + 20].numeroPiece = (unsigned char)(i + 20);
		PIECE[i + 30].c1 = c1;
		PIECE[i + 30].c2 = c2;
		PIECE[i + 30].c3 = c3;
		PIECE[i + 30].numeroPiece = (unsigned char)(i + 30);
	}
	PIECE[0].numeroPiece = 0;
	return 0;
}

/*!
 * \brief retourne une case d'un coup
 * \param coupJoueur coup du joueur
 * \param [out] tab tableau contenant les cases
 * \return -1 si une case contient un pointeur null
 * \return 0 si tout c'est bien passé
 */
int getCasesFromCoup(coup coupJoueur, historiqueCase * tab[3])
{
	int x1, x3, y1, y3;
	tab[1] = getCase(coupJoueur.xCoup, coupJoueur.yCoup);
	x1 = coupJoueur.xCoup;
	y1 = coupJoueur.yCoup;
	x3 = coupJoueur.xCoup;
	y3 = coupJoueur.yCoup;
	switch (coupJoueur.orientationPiece) {
	case HD:
		y1 += 1;
		x3 += 1;
		break;
	case BD:
		x1 += 1;
		y3 -= 1;
		break;
	case BG:
		y1 -= 1;
		x3 -= 1;
		break;
	case HG:
		x1 -= 1;
		y3 += 1;
		break;
	default:
		return -1;
	}
	tab[0] = getCase(x1, y1);
	tab[2] = getCase(x3, y3);
	if (tab[0] == NULL || tab[1] == NULL || tab[2] == NULL) {
		return -1;
	}
	return 0;

}
