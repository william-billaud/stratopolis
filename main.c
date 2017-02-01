/**
* \file main.c
* \brief fichier main
* \author billaud william
* \author Hipault Theo
* \date 22/01/2107
*/

#include "affichage.h"
#ifndef M_PI
#define M_PI 3.14
#endif

/// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 800
#define HauteurFenetre 600

/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement);

int main(int argc, char **argv)
{
	initialiseGfx(argc, argv);

	prepareFenetreGraphique("OpenGL", LargeurFenetre, HauteurFenetre);

	/* Lance la boucle qui aiguille les evenements sur la fonction gestionEvenement ci-apres,
	   qui elle-meme utilise fonctionAffichage ci-dessous */
	lanceBoucleEvenements();

	return 0;
}

/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement)
{
	static bool pleinEcran = false;	// Pour savoir si on est en mode plein ecran ou pas

	/* On va aussi animer une balle traversant l'ecran */
	static int xBalle;
	static int yBalle;
	static int vxBalle = 7;
	static int vyBalle = -7;

	switch (evenement) {
	case Initialisation:
		xBalle = (int)(largeurFenetre() * valeurAleatoire());
		yBalle = (int)(hauteurFenetre() * valeurAleatoire());
		/* Le message "Initialisation" est envoye une seule fois, au debut du
		   programme : il permet de fixer "image" a la valeur qu'il devra conserver
		   jusqu'a la fin du programme : soit "image" reste a NULL si l'image n'a
		   pas pu etre lue, soit "image" pointera sur une structure contenant
		   les caracteristiques de l'image "imageNB.bmp" */

		// Configure le systeme pour generer un message Affichage
		// environ 50 fois par seconde
		demandeAnimation_ips(50);
		break;

	case Affichage:

		// On part d'un fond d'ecran blanc
		effaceFenetre(255, 255, 255);

		// Affichage d'une ligne bleue
		couleurCourante(0, 0, 255);
		epaisseurDeTrait(10);
		ligne(0, 0, (largeurFenetre() - 600) / 2,
		      (hauteurFenetre() - 400) / 2);

		// Affichage d'un rectangle "saumon"
		couleurCourante(255, 128, 128);
		rectangle((largeurFenetre() - 600) / 2,
			  (hauteurFenetre() - 400) / 2,
			  (largeurFenetre() - 600) / 2 + 600,
			  (hauteurFenetre() - 400) / 2 + 400);

		// Affichage d'un texte vert sombre avec ombrage en police de taille 20
		// L'effet d'ombrage vient tout simplement du dessin du texte en gris clair
		// sous le texte voulu, avec un léger décalage
		couleurCourante(210, 210, 210);
		epaisseurDeTrait(3);
		afficheChaine("L'algo c'est rigolo", 20, 77, 13);
		couleurCourante(0, 128, 0);
		epaisseurDeTrait(2);
		afficheChaine("L'algo c'est rigolo", 20, 75, 15);

		// Affichage d'une balle rouge
		couleurCourante(255, 0, 0);
		cercle(xBalle, yBalle, 10);

		// On met a jour les coordonnees de la balle
		xBalle += vxBalle;
		yBalle += vyBalle;

		// On fait rebondir la balle si necessaire
		if (xBalle < 0 || xBalle >= largeurFenetre())
			vxBalle = -vxBalle;
		if (yBalle < 0 || yBalle >= hauteurFenetre())
			vyBalle = -vyBalle;
		break;

	case Clavier:
		printf("%c : ASCII %d\n", caractereClavier(),
		       caractereClavier());

		switch (caractereClavier()) {
		case 'Q':	/* Pour sortir quelque peu proprement du programme */
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
			// Si le bouton gauche de la souris est appuye, faire repartir
			// la balle de la souris
			xBalle = abscisseSouris();
			yBalle = ordonneeSouris();
		} else if (etatBoutonSouris() == GaucheRelache) {
			printf("Bouton gauche relache en : (%d, %d)\n",
			       abscisseSouris(), ordonneeSouris());
		}
		break;

	case Souris:		// Si la souris est deplacee
		break;

	case Inactivite:	// Quand aucun message n'est disponible
		break;

	case Redimensionnement:	// La taille de la fenetre a ete modifie ou on est passe en plein ecran
		// Donc le systeme nous en informe
		if (xBalle >= largeurFenetre())
			xBalle = largeurFenetre() - 1;
		if (yBalle >= hauteurFenetre())
			yBalle = hauteurFenetre() - 1;
		printf("Largeur : %d\t", largeurFenetre());
		printf("Hauteur : %d\n", hauteurFenetre());
		break;
	}
}
