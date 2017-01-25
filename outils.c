/*!
* \file outils.c
* \brief fichier contenant les outils utils à tous les autres modules
* \author billaud
* \author hipault
* \date 22/01/17
*/

#include "outils.h"

/**\var variable global contenant le plateau*/
extern PLATEAU plat;

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
int getHauteurCase(historiqueCase c)
{
	char i = c.hauteur;
	if (i < 0 || i > 19) {
		i = -1;
	}
	return i;
}

/*!
\brief retourne la couleur d'une case
\param[in] c  case dont la couleur est demandé
\return couleur de la case
\return -1 en case d'erreur
*/
int getCouleurCase(historiqueCase c)
{

	if (getHauteurCase(c) == -1) {
		return -1;
	} else {
		return c.tabEtage[(int)c.hauteur].couleurEtage;
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
int getNumeroPiece(historiqueCase c)
{
	int h = getHauteurCase(c);
	int numero;
	if (h == -1) {
		return -2;
	}
	numero = c.tabEtage[h].numeroPiece;
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
couleur couleurPiece(int numeroPiece,int numeroTuile){

    if(numeroPiece<0 || numeroPiece>41)
    {
        return neutre;

    } else{
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