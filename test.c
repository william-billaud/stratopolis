/*!
* \file test.c
* \brief fichier de test
* \author billaud
* \author Hipault
* \date 22/01/17
*/

#include "affichage.h"

extern PLATEAU plat;
/**<\var variable global contenant le plateau*/

extern pieces PIECE[42];

extern ORDREPIECE ordreJoueurs[2];
/**<\var tableau contenant l'ordre des pièces des joueurs*/

/**
 * \brief fonction main de test
 * \return int 0 ( tout c'est bien passé)
 */

void gestionEvenement(EvenementGfx evenement)
{
	puts("rien");
}
int main(void)
{
	initPlateau();
	initPiece();
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
	printf(possedeTuileAdjacente(85, 85) ? "vrai\n" : "faux\n");
	int j;
	for (j = 0; j < 41; ++j) {
		printf("pieces numero : %2d , c1 = %d , c2 = %d, c3= %d \n",
		       PIECE[j].numeroPiece, PIECE[j].c1, PIECE[j].c2,
		       PIECE[j].c3);
	}
	coup cp;
	cp.numeroPiece = 14;
	cp.xCoup = 82;
	cp.yCoup = 80;
	cp.orientationPiece = HD;
	printf("joue le coup %d\n", joueCoup(cp));
	/*printf("dejoue le coup %d\n", dejoueCoup(cp));*/
	printf("le score du joueur 1 est de : %d \n",calculScore(1));
	printf("le score du joueur 2 est de : %d \n",calculScore(2));

	return 0;
}
