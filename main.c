/**
* \file main.c
* \brief fichier main
* \author Billaud William
* \author Hipault Theo
* \date 22/01/2107
*/

#include "affichage.h"

#define LargeurFenetre 800
#define HauteurFenetre 600

void gestionEvenement(EvenementGfx evenement);

int main(int argc, char **argv)
{
	initialiseGfx(argc, argv);
	prepareFenetreGraphique("OpenGL", LargeurFenetre, HauteurFenetre);
	lanceBoucleEvenements();
	return 0;
}

void gestionEvenement(EvenementGfx evenement)
{
	static bool pleinEcran = false;	// Pour savoir si on est en mode plein ecran ou pas

	switch (evenement) {
	case Initialisation:
		printf("%s\n", "Initialisation");
		initPiece();
		initPlateau();

		demandeAnimation_ips(50);
		break;

	case Affichage:
		effaceFenetre(255, 255, 255);
		afficheGrille(3);
		break;

	case Clavier:
		printf("%c : ASCII %d\n", caractereClavier(),
		       caractereClavier());

		switch (caractereClavier()) {
		case 'Q':
		case 'q':
			exit(0);

		case 'F':
		case 'f':
			pleinEcran = !pleinEcran;	// Changement de mode plein ecran
			if (pleinEcran)
				modePleinEcran();
			else
				redimensionneFenetre(LargeurFenetre,
						     HauteurFenetre);
			break;

		case 'R':
		case 'r':
			// On force un rafraichissement
			rafraichisFenetre();
			break;
		default:
			break;
		}
		break;

	case ClavierSpecial:
		printf("ASCII %d\n", toucheClavier());
		break;

	case BoutonSouris:
		if (etatBoutonSouris() == GaucheAppuye) {
			printf("Bouton gauche appuye en : (%d, %d)\n",
			       abscisseSouris(), ordonneeSouris());
		} else if (etatBoutonSouris() == GaucheRelache) {
			printf("Bouton gauche relache en : (%d, %d)\n",
			       abscisseSouris(), ordonneeSouris());
		}
		break;

	case Souris:
		break;

	case Inactivite:
		break;

	case Redimensionnement:
		printf("Largeur : %d\t", largeurFenetre());
		printf("Hauteur : %d\n", hauteurFenetre());
		break;
	}
}
