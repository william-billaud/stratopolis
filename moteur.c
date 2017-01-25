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
		ordreJoueurs[joueur - 1][i] = liste[r]+20*(joueur-1);
		//sa place dans la liste est remplacé par la celle la plus en haut du tableau
		liste[r] = liste[n];
	}
	// on ajoute le dernier terme
	ordreJoueurs[joueur - 1][19] = liste[0]+20*(joueur-1);

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
    historiqueCase * tab[4];
    int i;
    tab[0]=getCase(x-1,y);
    tab[1]=getCase(x+1,y);
    tab[2]=getCase(x,y+1);
    tab[3]=getCase(x,y-1);
    for (i = 0; i < 4; ++i) {
        if(getHauteurCase(*tab[i])>0)
        {
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
bool estValideSuperposition(couleur haut,couleur bas)
{
    if((haut==rouge && bas==vert) || (haut==bas && bas==rouge))
    {
        return false;
    } else
    {
        return true;
    }
}

/*!
\brief verifie qu'un coup est valide
\param[in] coupJoueur coup du joueur
\return true si le coup est valide
\return false si le coup n'est pas possible
*/
bool estValideCoup(coup coupJoueur){
    historiqueCase *c1,*c2,*c3;
    int x1,x3,y1,y3;
    c2=getCase(coupJoueur.xCoup,coupJoueur.yCoup);
    x1=coupJoueur.xCoup;
    y1=coupJoueur.yCoup;
    x3=coupJoueur.xCoup;
    y3=coupJoueur.yCoup;
    switch (coupJoueur.orientationPiece)
    {
        case HD:
            y1+=1;
            x3+=1;
            break;
        case BD:
            x1+=1;
            y3-=1;
            break;
        case BG:
            y1-=1;
            x3-=1;
            break;
        case HG:
            x1-=1;
            y3+=1;
            break;
        default:
            return false;
    }
    c1=getCase(x1,y1);
    c3=getCase(x3,y3);
    if(c1==NULL || c3==NULL || c2 ==NULL)
    {
        return false;
    }
    if(getHauteurCase(*c1)!=getHauteurCase(*c2) || getHauteurCase(*c1)!= getHauteurCase(*c3))
    {
        return false;
    }
    if(getHauteurCase(*c1)==0)
    {
        if(possedeTuileAdjacente(x1,y1)==false && possedeTuileAdjacente(x3,y3)==false && false==possedeTuileAdjacente(coupJoueur.xCoup,coupJoueur.yCoup))
        {
            return false;
        }
    } else{
        if(!estValideSuperposition( couleurPiece(coupJoueur.numeroPiece,1),(couleur)getCouleurCase(*c1)) || !estValideSuperposition( couleurPiece(coupJoueur.numeroPiece,2),(couleur)getCouleurCase(*c2)) || !estValideSuperposition( couleurPiece(coupJoueur.numeroPiece,3),(couleur)getCouleurCase(*c3)))
        {
            return false;
        }

    }
    if(getNumeroPiece(*c1)==getNumeroPiece(*c2) && getNumeroPiece(*c1)==getNumeroPiece(*c3))
    {
        return false;
    }
    return true;
}
