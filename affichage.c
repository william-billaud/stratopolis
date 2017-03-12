/*!
* \file affichage.c
* \brief fichier contenant les fonctions d'affichages
* \author billaud et hipault
* \date 22/01/17
*/

#include "affichage.h"

/* Fonction de trace de cercle */
void cercle(float centreX, float centreY, float rayon)
{
	const int Pas = 20;	// Nombre de secteurs pour tracer le cercle
	const double PasAngulaire = 2. * 3.14 / Pas;
	int index;

	for (index = 0; index < Pas; ++index)	// Pour chaque secteur
	{
		const double angle = 2. * 3.14 * index / Pas;	// on calcule l'angle de depart du secteur
		triangle(centreX, centreY,
			 (float)(centreX + rayon * cos(angle)),
			 (float)(centreY + rayon * sin(angle)),
			 (float)(centreX + rayon * cos(angle + PasAngulaire)),
			 (float)(centreY + rayon * sin(angle + PasAngulaire)));
		// On trace le secteur a l'aide d'un triangle => approximation d'un cercle
	}
}

/*!
   \brief Affiche le plateau de jeu, la couleur et la hauteur de chaque case
	 \param[in] zoom : niveau de zoom (minimum 1, maximum 81)
	 \return rien
*/
void afficheGrille(unsigned int zoom)
{
	//Bloque le nombre maximum de cases à afficher
	if (zoom < 1) {
		zoom = 1;
	}
	if (zoom > 81) {
		zoom = 81;
	}

	float largeur = largeurFenetre();
	float hauteur = hauteurFenetre();
	//Définit l'écart entre le centre de la fenêtre et le bord du plateau
	float ecart = ((largeur <= hauteur) * largeur
		       + (largeur > hauteur) * hauteur) / 2.5;
	float taille_case = ecart / zoom;
	historiqueCase *maCase, *case_h, *case_b, *case_g, *case_d;
	float minXcase, minYcase, maxXcase, maxYcase, margeH, margeB, margeG,
	    margeD;
	char hauteurCase[20];

	//Affiche une bordure du plateau de 5 pixels
	couleurCourante(200, 200, 200);
	rectangle(largeur / 2 - ecart - 5,
		  hauteur / 2 - ecart - 5,
		  largeur / 2 + ecart + 5, hauteur / 2 + ecart + 5);

	//Parcours du plateu de jeu
	for (unsigned int i = (81 - zoom); i < (81 + zoom); i++) {
		for (unsigned int j = (81 - zoom); j < (81 + zoom); j++) {

			minXcase =
			    largeur / 2 - ecart + (i - 81 + zoom) * taille_case;
			minYcase =
			    hauteur / 2 - ecart + (j - 81 + zoom) * taille_case;
			maxXcase =
			    largeur / 2 - ecart + (i - 80 + zoom) * taille_case;
			maxYcase =
			    hauteur / 2 - ecart + (j - 80 + zoom) * taille_case;

			//Récupère la pièce courante t les pieces adjacentes
			maCase = getCase(i, j);
			case_h = getCase(i, j + 1);
			case_b = getCase(i, j - 1);
			case_g = getCase(i - 1, j);
			case_d = getCase(i + 1, j);

			//Détermine les contours de la pièce
			margeH =
			    (getNumeroPiece(*case_h) != getNumeroPiece(*maCase))
			    || (getHauteurCase(*case_h) !=
				getHauteurCase(*maCase));
			margeB =
			    (getNumeroPiece(*case_b) != getNumeroPiece(*maCase))
			    || (getHauteurCase(*case_b) !=
				getHauteurCase(*maCase));
			margeG =
			    (getNumeroPiece(*case_g) != getNumeroPiece(*maCase))
			    || (getHauteurCase(*case_g) !=
				getHauteurCase(*maCase));
			margeD =
			    (getNumeroPiece(*case_d) != getNumeroPiece(*maCase))
			    || (getHauteurCase(*case_d) !=
				getHauteurCase(*maCase));

			//Trace le contour
			couleurCourante(58, 41, 20);
			rectangle(minXcase + margeG, minYcase + margeB,
				  maxXcase - margeD, maxYcase - margeH);

			//Determine la coueur de la case
			couleur couleurCase = getCouleurCase(*maCase);
			switch (couleurCase) {
			case neutre:
				couleurCourante(135, 87, 39);
				break;
			case rouge:
				couleurCourante(247, 35, 12);
				break;
			case vert:
				couleurCourante(58, 242, 75);
				break;
			case vide:
				couleurCourante(78, 61, 40);
				break;
			}

			//Trace la pièce
			rectangle(minXcase + margeG + 2,
				  minYcase + margeB + 2,
				  maxXcase - margeD - 2, maxYcase - margeH - 2);
			//Affiche la hauteur de la case
			if (couleurCase != vide) {
				sprintf(hauteurCase, "%d",
					getHauteurCase(*maCase));
				couleurCourante(240, 255, 255);
				epaisseurDeTrait(2);
				afficheChaine(hauteurCase, taille_case / 4,
					      minXcase +
					      tailleChaine(hauteurCase,
							   taille_case),
					      minYcase + taille_case / 4.5);
			}
		}
	}
}
