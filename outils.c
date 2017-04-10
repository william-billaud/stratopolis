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
		PIECE[i + 30].c1 = c1;
		PIECE[i + 30].c2 = c2;
		PIECE[i + 30].c3 = c3;
		PIECE[i + 30].numeroPiece = (unsigned char)(i + 30);
		PIECE[i + 20].c1 = c1;
		PIECE[i + 20].c2 = c2;
		PIECE[i + 20].c3 = c3;
		PIECE[i + 20].numeroPiece = (unsigned char)(i + 20);
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
		PIECE[i + 10].c1 = c1;
		PIECE[i + 10].c2 = c2;
		PIECE[i + 10].c3 = c3;
		PIECE[i + 10].numeroPiece = (unsigned char)(i + 10);
		PIECE[i].c1 = c1;
		PIECE[i].c2 = c2;
		PIECE[i].c3 = c3;
		PIECE[i].numeroPiece = (unsigned char)(i);
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

/*!
 * \brief calcul le minimum entre deux valeurs
 * \param a
 * \param b
 * \return minimum entre a et b
 */
int min(int a, int b)
{
	return (a > b) ? b : a;
}

/*!
 * \brief retourne le maximum entre a et b
 * \param a
 * \param b
 * \return
 */
int max(int a, int b)
{
	return (a > b) ? a : b;
}

/*!
 * \brief trouve le meilleur zooom pour le cadrage actuelle
 * \param [out] x pointeur vers l'abscisse du meilleur zoom
 * \param [out] y pointeur vers l'ordonnée du meilleur zoom
 * \param [out] zoom pointeur vers le meilleur zoom
 * \return -1 en cas d'erreur
 * \return 0 si non
 */
int trouveMeilleurZoom(unsigned int *x, unsigned int *y, unsigned int *zoom)
{
	int x_min = 0, x_max = 0, y_min = 0, y_max = 0;
	int i = 0, j = 0, c = 0;
	int zoomTmp;
	bool haut = true, bas = true, gauche = true, droite = true;
	//tant que les coordonnés du point le plus en bas à droite et celui en haut à gauche n'ont pas été trouvée
	while ((haut || bas || droite || gauche)
	       && (c <= ((TAILLEMAX - 1) * (TAILLEMAX - 1)))) {
		i = c % TAILLEMAX;
		j = c / TAILLEMAX;
		if (gauche && vide != getCouleurCase(getCase(i, j))) {
			y_min = j;
			gauche = false;
		}
		if (bas && vide != getCouleurCase(getCase(j, i))) {
			x_min = j;
			bas = false;
		}
		if (droite && vide != getCouleurCase(getCase(TAILLEMAX - i - 1,
							     TAILLEMAX - j -
							     1))) {
			y_max = TAILLEMAX - j - 1;
			droite = false;
		}
		if (haut && vide !=
		    getCouleurCase(getCase
				   (TAILLEMAX - j - 1, TAILLEMAX - i - 1))) {
			x_max = TAILLEMAX - j - 1;
			haut = false;
		}
		c += 1;
	}
	if (c == ((TAILLEMAX - 1) * (TAILLEMAX - 1))) {
		return -1;
	}
	//on laisse, si possible une marge de 2 carreau
	x_min = x_min - 2;
	y_min = y_min - 2;
	y_max = y_max + 2;
	x_max = x_max + 2;
	//mise en place des plancher(0) et des saturation (TAILLEMAX-1) des valeurs
	x_min = (x_min > 0) ? x_min : 0;
	y_min = (y_min > 0) ? y_min : 0;
	y_max = (y_max < TAILLEMAX) ? y_max : TAILLEMAX - 1;
	x_max = (x_max < TAILLEMAX) ? x_max : TAILLEMAX - 1;
	//le zoom vaut l'ecart maximum entre les abscisse ou les ordonnée
	//centrage des pièces
	if ((x_max - x_min) > (y_max - y_min)) {
		zoomTmp = (x_max - x_min) + 1;
		y_min = y_min - ((zoomTmp - (y_max - y_min)) / 2);
		y_min = (y_min > 0) ? y_min : 0;
	} else {
		zoomTmp = (y_max - y_min) + 1;
		x_min = x_min - ((zoomTmp - (x_max - x_min)) / 2);
		x_min = (x_min > 0) ? x_min : 0;
	}
	*y = (unsigned int)y_min;
	*x = (unsigned int)x_min;
	*zoom = (unsigned int)zoomTmp;
	return 0;
}

/*!
 * \brief fonction permettant de gèrer le temp
 * \param ordre 0 pour reinitialiser le temp stocké, n'importe quel nombre pour récuperer le temp stocké
 * \return le temp stocké
 * \return 0 si il a été reinitialisé
 */
int gestionDuree(int ordre)
{
	static int temp;
	if(ordre==0)
	{
		temp=(int) time(NULL);
		return 0;
	}else
	{
		return temp;
	}
}
