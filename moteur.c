/*!
* \file moteur.c.c
* \brief fichier contenant les fonction utils au moteur du jeu
* \author billaud
* \author hipault
* \date 22/01/17
*/

#include "moteur.h"

/**<\var variable global contenant le plateau*/
extern PLATEAU  plat;
/*!
 * \brief initialise le plateau (pose la pièce initiale)
 * \return 0 si tout c'est bien passé
 * \return -1 si un problème a eu lieu
 */
int initPlateau(void)
{
    int i_x;/**<\var index des abscisse*/
    int i_y;/**<\var indes des ordonées*/

    for (i_x = 0; i_x <TAILLEMAX; ++i_x) {
        for (i_y = 0; i_y < TAILLEMAX; ++i_y) {
            setCaseAZero(&(plat[i_x][i_y]));
        }
    }
    //pose la pièce de depart (pièce numero 0)
    plat[80][80].hauteur=1;
    plat[80][80].tabEtage[1].couleurEtage=vert;
    plat[80][80].tabEtage[1].numeroPiece=0;
    plat[81][80].hauteur=1;
    plat[81][80].tabEtage[1].couleurEtage=rouge;
    plat[81][80].tabEtage[1].numeroPiece=0;
    return 0;
}

/*!
 * \brief choisis le joueur qui commenceras
 * \return 1 si le joueur 1 commenceras
 * \return 2 si le joueur 2 commenceras
 */
int choisisJoueur(void)
{
    /* recupère le timestamp actuelle et le stock dans a)*/
    unsigned int a=(unsigned int)time(NULL);/**<\var seed recupere a partir du timestamp*/
    //defini la seed du lancer aléatoire
    srand(a);
    //effectue le lancer aléatoire et redui les possibilité à 1 ou 2
    return rand()%2+1;
}