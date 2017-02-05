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

void afficheGrille(unsigned int zoom)
{
	if (zoom < 1) {
		zoom = 1;
	}
	if (zoom > 81) {
		zoom = 81;
	}

	int i, j;
	int diagInf = 81 - zoom;
	int diagSup = 81 + zoom;
	float milieuX = largeurFenetre() / 2;
	float milieuY = hauteurFenetre() / 2;
	float ecart = 2 * compare(milieuX, milieuY, false) / 3;

	float hauteur_zone_min = milieuY - ecart;
	float largeur_zone_min = milieuX - ecart;
	float largeur_zone_max = milieuX + ecart;

	float taille_case =
	    ((largeur_zone_max - largeur_zone_min) / (diagSup - diagInf));

	for (i = diagInf; i < diagSup; i++) {
		float caseXmin = largeur_zone_min + (i - diagInf) * taille_case;
		for (j = diagInf; j < diagSup; j++) {
			float caseYmin =
			    hauteur_zone_min + (j - diagInf) * taille_case;
			historiqueCase *maCase = getCase(i, j);
			couleur couleurCase = getCouleurCase(*maCase);
			if (couleurCase == neutre) {
				couleurCourante(78, 61, 40);
			} else if (couleurCase == rouge) {
				couleurCourante(247, 35, 12);
			} else if (couleurCase == vert) {
				couleurCourante(58, 242, 75);
			}
			if (couleurCase != vide) {
				cercle(caseXmin + (taille_case / 2),
				       caseYmin + (taille_case / 2),
				       (taille_case / 2));

				/*couleurCourante(240, 255, 255);
				   afficheChaine("1", taille_case,
				   caseXmin + (taille_case / 2),
				   caseYmin + (taille_case / 2));
				 */
			}
		}
	}
}
