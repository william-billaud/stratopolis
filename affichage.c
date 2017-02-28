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
	if (zoom < 1) {
		zoom = 1;
	}
	if (zoom > 81) {
		zoom = 81;
	}

	int i, j, numero;
	char hauteur[2];
	int diagInf = 81 - zoom;
	int diagSup = 81 + zoom;

	float ecart =
	    2 * compare(largeurFenetre() / 2, hauteurFenetre() / 2, false) / 3;

	float h_zone_min = (hauteurFenetre() / 2) - ecart;
	float h_zone_max = (hauteurFenetre() / 2) + ecart;
	float l_zone_min = (largeurFenetre() / 2) - ecart;
	float l_zone_max = (largeurFenetre() / 2) + ecart;

	historiqueCase *maCase;
	historiqueCase *case_h;
	historiqueCase *case_b;
	historiqueCase *case_g;
	historiqueCase *case_d;

	float taille_case = ((l_zone_max - l_zone_min) / (diagSup - diagInf));
	couleur couleurCase;

	//Affiche une bordure du plateau
	couleurCourante(200, 200, 200);
	rectangle(l_zone_min - 5, h_zone_min - 5,
		  l_zone_max + 5, h_zone_max + 5);
	couleurCourante(58, 41, 20);
	rectangle(l_zone_min, h_zone_min, l_zone_max, h_zone_max);

	//Parcours du plateu de jeu
	for (i = diagInf; i < diagSup; i++) {
		float caseXmin = l_zone_min + (i - diagInf) * taille_case;
		for (j = diagInf; j < diagSup; j++) {
			float caseYmin =
			    h_zone_min + (j - diagInf) * taille_case;

			maCase = getCase(i, j);
			case_h = getCase(i, j + 1);
			case_b = getCase(i, j - 1);
			case_g = getCase(i - 1, j);
			case_d = getCase(i + 1, j);

			//Determine la coueur de la case
			couleurCase = getCouleurCase(*maCase);
			if (couleurCase == neutre) {
				couleurCourante(255, 255, 255);
			} else if (couleurCase == rouge) {
				couleurCourante(247, 35, 12);
			} else if (couleurCase == vert) {
				couleurCourante(58, 242, 75);
			}
			if (couleurCase != vide) {
				//Trace la case
				rectangle(caseXmin, caseYmin,
					  caseXmin + taille_case,
					  caseYmin + taille_case);

				//Determine les contours de la pièce
				/*numero = getNumeroPiece(*maCase);
				   (numero != getNumeroPiece(*case_h));
				   (numero != getNumeroPiece(*case_b));
				   (numero != getNumeroPiece(*case_g));
				   (numero != getNumeroPiece(*case_d));
				 */

				//Affiche la hauteur de la case
				sprintf(hauteur, "%d", getHauteurCase(*maCase));
				couleurCourante(240, 255, 255);
				epaisseurDeTrait(3);
				afficheChaine("1", taille_case / 2,
					      caseXmin + tailleChaine("1",
								      taille_case
								      / 2),
					      caseYmin + tailleChaine("1",
								      taille_case
								      / 2));

			} else {
				//Trace le fond de la case
				couleurCourante(78, 61, 40);
				rectangle(caseXmin + 1, caseYmin + 1,
					  caseXmin + taille_case - 1,
					  caseYmin + taille_case - 1);
			}
		}
	}
}
