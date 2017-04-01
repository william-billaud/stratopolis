/**
* \file main.c
* \brief fichier main
* \author Billaud William
* \author Hipault Theo
* \date 22/01/2107
*/

#include "affichage.h"

#define LargeurFenetre 800
/// hauteur par defaut d'une image correspondant a nos critères
#define HauteurFenetre 600

void gestionEvenement(EvenementGfx evenement);

/**
 * \brief fonction main
 * \param argc nombre d'argument
 * \param argv tableau contenant les argument
 * \return 0 si tout est bon
 */
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
	//position du zoom par defaut
	static unsigned int x_d = 80, y_d = 80;
	static unsigned int zoom_d = 20;
	int x, y;
	static coup coupJoueur;
	static orientation orientationPiece;
	//static int joueurActuelle;
	switch (evenement) {
	case Initialisation:
		printf("%s\n", "Initialisation");
		initPiece();
		initOrdrePieces(1);
		initOrdrePieces(2);
		initPlateau();
		coup cp;
		cp.numeroPiece = 14;
		cp.xCoup = 82;
		cp.yCoup = 80;
		cp.orientationPiece = HD;
		joueCoup(cp);
		cp.numeroPiece = 10;
		cp.xCoup = 84;
		cp.yCoup = 80;
		cp.orientationPiece = HD;
		joueCoup(cp);
		cp.numeroPiece = 23;
		cp.yCoup = 80;
		cp.xCoup = 82;
		cp.orientationPiece = HG;
		joueCoup(cp);
		trouveMeilleurZoom(&x_d, &y_d, &zoom_d);
		//joueurActuelle = choisisJoueur();

		detecteCase(&x, &y, zoom_d, x_d, y_d);
		coupJoueur.orientationPiece = orientationPiece;
		coupJoueur.yCoup = (unsigned int)y;
		coupJoueur.xCoup = (unsigned int)x;
		coupJoueur.numeroPiece = ordreJoueurs[0][0];

		activeGestionDeplacementPassifSouris();
		demandeAnimation_ips(50);
		break;

	case Affichage:
		effaceFenetre(255, 255, 255);
		afficheInterface("Joueur 1", "Joueur 2");
		afficheGrille(zoom_d, x_d, y_d);

		detecteCase(&x, &y, zoom_d, x_d, y_d);
		coupJoueur.orientationPiece = orientationPiece;
		coupJoueur.yCoup = (unsigned int)y;
		coupJoueur.xCoup = (unsigned int)x;
		coupJoueur.numeroPiece = ordreJoueurs[0][0];

		affichePredictif(coupJoueur, zoom_d);
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

		case 'Z':
		case 'z':
			trouveMeilleurZoom(&x_d, &y_d, &zoom_d);
			printf("X : %d, Y : %d ZOOM : %d \n", x_d, y_d, zoom_d);
			rafraichisFenetre();
			break;

		default:
			break;
		}
		break;

	case ClavierSpecial:
		printf("ASCII %d\n", toucheClavier());
		switch (toucheClavier()) {
		case ToucheFlecheDroite:
			if (orientationPiece == HG) {
				orientationPiece = HD;
			} else {
				orientationPiece += 1;
			}
			rafraichisFenetre();
			break;

		case ToucheFlecheGauche:
			if (orientationPiece == HD) {
				orientationPiece = HG;
			} else {
				orientationPiece -= 1;
			}
			rafraichisFenetre();
			break;

		default:
			break;
		}

		break;

	case BoutonSouris:
		if (etatBoutonSouris() == GaucheAppuye) {
			detecteCase(&x, &y, zoom_d, x_d, y_d);
			coupJoueur.orientationPiece = orientationPiece;
			coupJoueur.yCoup = (unsigned int)y;
			coupJoueur.xCoup = (unsigned int)x;
			coupJoueur.numeroPiece = ordreJoueurs[0][0];
			joueCoup(coupJoueur);
			printf("Bouton gauche appuye en : (%d, %d)\n", x, y);
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
