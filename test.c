/*!
* \file test.c
* \brief fichier de test
* \author billaud
* \author Hipault
* \date 22/01/17
*/

#include "affichage.h"
/**\var variable global contenant le plateau*/
extern PLATEAU plat;

extern pieces PIECE[42];

/**\var tableau contenant l'ordre des pièces des joueurs*/
extern ORDREPIECE ordreJoueurs[2];

int main(void)
{
	initPlateau();
	historiqueCase *c;
	//test get hauteur
	printf("getHauteur : %d \n", getHauteurCase(plat[80][80]));
	//test get couleur
	printf("getCouleur : %d \n", getCouleurCase(plat[81][80]));
	//test erreur getNumeroPiece
	c = getCase(89, 80);
	c->tabEtage[0].numeroPiece = 3;
	printf("getNumeroPiece : %d \n", getNumeroPiece(*c));
	printf("rand : %d \n", choisisJoueur());
	int b[20];
	int i;
	for (i = 0; i < 20; ++i) {
		b[i] = i;
	}
	printf(inArrayIny(&b[10], 10, 10) ? "vrai" : "faux");

	printf("\n \t \t tirage au sort \n");
	initOrdrePieces(1);
	initOrdrePieces(2);
	int k;
	for (k = 0; k < 20; ++k) {
		printf("%2d : %2d \t %2d : %2d  \n", k, ordreJoueurs[0][k], k,
		       ordreJoueurs[1][k]);
	}
	printf(possedeTuileAdjacente(85,85) ? "vrai" : "faux");
	return 0;
}
