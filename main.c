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
	static bool pleinEcran = true;	// Pour savoir si on est en mode plein ecran ou pas
	static enum {
		menu, classique, IA, victoire
	} mode;
	//position du zoom par defaut
	static unsigned int x_d = 80, y_d = 80;
	static unsigned int zoom_d = 20;
	int x, y;
	static coup coupJoueur;
	static orientation orientationPiece;
	static int joueurActuelle;
	switch (evenement) {
	case Initialisation:
		modePleinEcran();
		printf("%s\n", "Initialisation");
		initPartie(&joueurActuelle);
		joueurActuelle = 0;
		trouveMeilleurZoom(&x_d, &y_d, &zoom_d);
		mode = IA;
		activeGestionDeplacementPassifSouris();
		break;
	case Affichage:
		effaceFenetre(255, 255, 255);
		switch (mode) {
		case IA:
			if (joueurActuelle == 1) {
				coupJoueur =
				    coupIA(joueurActuelle, 2,
					   ordreJoueurs[0][20] +
					   ordreJoueurs[1][20]);
				if (joueCoup(coupJoueur) == 1) {
					ordreJoueurs[joueurActuelle][20] += 1;
					joueurActuelle =
					    (joueurActuelle + 1) % 2;
					trouveMeilleurZoom(&x_d, &y_d, &zoom_d);
					if (ordreJoueurs[1][20] == 20
					    && ordreJoueurs[0][20] == 20) {
						if (calculScore(1) >
						    calculScore(0)) {
							puts("joueur vert à gagné");
						} else {
							puts("joueur rouge à gagné");
						}
						initPartie(&joueurActuelle);
					}
				} else {
					puts("IA deconne grave");
				}
			}
		case classique:
			afficheInterface("WILLIAM", "THEO", joueurActuelle);
			afficheGrille(zoom_d, x_d, y_d);

			detecteCase(&x, &y, zoom_d, x_d, y_d);
			coupJoueur.orientationPiece = orientationPiece;
			coupJoueur.yCoup = (unsigned int)y;
			coupJoueur.xCoup = (unsigned int)x;
			coupJoueur.numeroPiece = (unsigned char)
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
			printf("1 %d: 2 : %d", calculScore(1), calculScore(2));
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
		switch (etatBoutonSouris()) {
		case GaucheAppuye:
			detecteCase(&x, &y, zoom_d, x_d, y_d);
			coupJoueur.orientationPiece = orientationPiece;
			coupJoueur.yCoup = (unsigned int)y;
			coupJoueur.xCoup = (unsigned int)x;
			coupJoueur.numeroPiece = (unsigned char)
			    ordreJoueurs[joueurActuelle][ordreJoueurs
							 [joueurActuelle][20]];
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
			break;
		case ScrollUp:
			if (toucheCtrlAppuyee()) {
				changeZoom(&x_d, &y_d, &zoom_d, true);
				printf("nouveau zoom : %d, %d :  %d \n", x_d,
				       y_d, zoom_d);
			} else {
				if (orientationPiece == HD) {
					orientationPiece = HG;
				} else {
					orientationPiece -= 1;
				}
			}
			break;
		case ScrollDown:
			if (toucheCtrlAppuyee()) {
				changeZoom(&x_d, &y_d, &zoom_d, false);
				printf("nouveau zoom : %d, %d %d \n", x_d, y_d,
				       zoom_d);
			} else {
				if (orientationPiece == HG) {
					orientationPiece = HD;
				} else {
					orientationPiece += 1;
				}
			}

			break;
		case TmpScroll:
			break;
		case GaucheRelache:
			break;
		case DroiteAppuye:
			break;
		case DroiteRelache:
			break;
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
		if (largeurFenetre() < 400 || hauteurFenetre() < 400) {
			redimensionneFenetre(400, 400);
		}
		printf("Largeur : %d\t", largeurFenetre());
		printf("Hauteur : %d\n", hauteurFenetre());
		rafraichisFenetre();
		break;
	}

}
