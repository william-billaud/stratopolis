/*!
* \file test.c
* \brief fichier de test
* \author billaud
* \author Hipault
* \date 22/01/17
*/

#include "affichage.h"
#include "moteur.h"
/**<\var variable global contenant le plateau*/
extern PLATEAU plat;

int main(void)
{
    initPlateau();
    historiqueCase *c;
    //test get hauteur
    printf("getHauteur : %d \n",getHauteurCase(plat[80][80]));
    //test get couleur
    printf("getCouleur : %d \n",getCouleurCase(plat[81][80]));
    //test erreur getNumeroPiece
    c=getCase(89,80);
    c->tabEtage[0].numeroPiece=3;
    printf("getNumeroPiece : %d \n",getNumeroPiece(*c));
    printf("rand : %d \n",choisisJoueur());
    printf("rand : %d \n",choisisJoueur());
    printf("rand : %d \n",choisisJoueur());
    return 0;
}