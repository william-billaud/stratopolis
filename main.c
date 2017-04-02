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
	static enum { menu, classique, IA, victoire } mode;
	//position du zoom par defaut
	static unsigned int x_d = 80, y_d = 80;
	static unsigned int zoom_d = 20;
	int x, y;
	static coup coupJoueur;
	static orientation orientationPiece;
	static int joueurActuelle;
	switch (evenement) {
	case Initialisation:
		printf("%s\n", "Initialisation");
		initPartie(&joueurActuelle);
		trouveMeilleurZoom(&x_d, &y_d, &zoom_d);

		detecteCase(&x, &y, zoom_d, x_d, y_d);
		mode = classique;
		activeGestionDeplacementPassifSouris();
		break;

	case Affichage:
		effaceFenetre(255, 255, 255);
		switch (mode) {
		case classique:
		case IA:
			afficheInterface("WILLIAM", "THEO");
			afficheGrille(zoom_d, x_d, y_d);

			detecteCase(&x, &y, zoom_d, x_d, y_d);
			coupJoueur.orientationPiece = orientationPiece;
			coupJoueur.yCoup = (unsigned int)y;
			coupJoueur.xCoup = (unsigned int)x;
			coupJoueur.numeroPiece =
			    (unsigned char)
			    ordreJoueurs[joueurActuelle][ordreJoueurs
							 [joueurActuelle][20]];
			affichePredictif(coupJoueur, zoom_d);
			break;
		case menu:
		case victoire:
			break;
		}

		break;

	case Clavier:
		printf("%c : ASCII %d\n", caractereClavier(),
		       caractereClavier());

		switch (caractereClavier()) {
		case 'Q':
		case 'q':
			termineBoucleEvenements();
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
			switch (mode) {
			case menu:
				break;
			case classique:
			case IA:
				trouveMeilleurZoom(&x_d, &y_d, &zoom_d);
				printf("X : %d, Y : %d ZOOM : %d \n", x_d, y_d,
				       zoom_d);
				break;
			case victoire:
				break;
			}

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
		case ToucheFlecheBas:
			if (orientationPiece == HG) {
				orientationPiece = HD;
			} else {
				orientationPiece += 1;
			}
			break;

		case ToucheFlecheGauche:
		case ToucheFlecheHaut:
			if (orientationPiece == HD) {
				orientationPiece = HG;
			} else {
				orientationPiece -= 1;
			}
			break;

		default:
			break;
		}
			rafraichisFenetre();
		break;

	case BoutonSouris:
		if (etatBoutonSouris() == GaucheAppuye) {
			detecteCase(&x, &y, zoom_d, x_d, y_d);
			coupJoueur.orientationPiece = orientationPiece;
			coupJoueur.yCoup = (unsigned int)y;
			coupJoueur.xCoup = (unsigned int)x;
			coupJoueur.numeroPiece =
			    (unsigned char)ordreJoueurs[joueurActuelle][ordreJoueurs[joueurActuelle][20]];
			orientationPiece = HD;
			if (joueCoup(coupJoueur) == 1) {
				ordreJoueurs[joueurActuelle][20] += 1;
				joueurActuelle = (joueurActuelle + 1) % 2;
				if (ordreJoueurs[1][20] == 20
				    && ordreJoueurs[0][20] == 20) {
					if (calculScore(0) > calculScore(1)) {
						puts("joueur vert à gagné");
					} else {
						puts("joueur rouge à gagné");
					}
					initPartie(&joueurActuelle);
				}
			}
		}else if(etatBoutonSouris()==ScrollDown)
		{
			if (orientationPiece == HG) {
				orientationPiece = HD;
			} else {
				orientationPiece += 1;
			}
		}else if(etatBoutonSouris()==ScrollUp)
		{
			if (orientationPiece == HD) {
				orientationPiece = HG;
			} else {
				orientationPiece -= 1;
			}
		}
		rafraichisFenetre();
		break;

	case Souris:

		rafraichisFenetre();
		break;

	case Inactivite:
		break;
	case Temporisation:
		break;

	case Redimensionnement:
		printf("Largeur : %d\t", largeurFenetre());
		printf("Hauteur : %d\n", hauteurFenetre());
		break;
	}

}
