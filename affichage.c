/*!
* \file affichage.c
* \brief fichier contenant les fonctions d'affichages
* \author billaud et hipault
* \date 22/01/17
*/

#include "affichage.h"

/* Fonction de trace de cercle */
/*
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
*/
/**
 * \brief Affiche le plateau de jeu, la couleur et la hauteur de chaque case
 * \param [in] zoom : nombre de case affiché par ligne/colonne
 * \param basX abscisse de la case du bas
 * \param basY abscisse de la case du bas
 */
void afficheGrille(unsigned int zoom, unsigned int basX, unsigned int basY)
{
	//Bloque le nombre maximum de cases à afficher
	if (zoom < 1) {
		zoom = 1;
	}
	if (zoom >= TAILLEMAX) {
		zoom = TAILLEMAX - 1;
	}
	if (basX + zoom >= TAILLEMAX) {
		basX = TAILLEMAX - 1 - zoom;
	}
	if (basY + zoom >= TAILLEMAX) {
		basY = TAILLEMAX - 1 - zoom;
	}

	float largeur = largeurFenetre();
	float hauteur = hauteurFenetre();
	//Définit l'écart entre le centre de la fenêtre et le bord du plateau
	float ecart = (float)(((largeur <= hauteur) * largeur
			       + (largeur > hauteur) * hauteur) / 2.5);
	float taille_case = 2 * ecart / zoom;
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
	unsigned int i;
	unsigned int j;
	for (i = (basX); i < (basX + zoom); i++) {
		for (j = (basY); j < (basY + zoom); j++) {

			minXcase =
			    largeur / 2 - ecart + (i - basX) * taille_case;
			//
			minYcase =
			    hauteur / 2 - ecart + (j - basY) * taille_case;
			maxXcase =
			    largeur / 2 - ecart + (i - basX + 1) * taille_case;
			maxYcase =
			    hauteur / 2 - ecart + (j - basY + 1) * taille_case;

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

			//Determine la couleur de la case
			couleur couleurCase = (couleur) getCouleurCase(*maCase);
			determineCouleur(couleurCase);

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
					      (float)(minYcase +
						      taille_case / 4.5));
			}
		}
	}
}

/*!
 * \brief appelle couleurCourante() en fonction du paramètre
 * \param [in]couleurCase couleur de la case à déterminer
 * \return rien
 */
void determineCouleur(couleur couleurCase)
{
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
}

/*!
   \brief Affiche l’interface de jeu
   \param[in] nomJ1 : nom du premier joueur
	 \param[in] nomJ2 : nom du deuxième joueur
	 \return rien
*/
void afficheInterface(char nomJ1[15], char nomJ2[15])
{
//      pieces pieceJ1 = PIECE[ordreJoueurs[0][20 - ordreJoueurs[0][20]]];
		/**< piece disponible pour le joueur 1*/
//      pieces pieceJ2 = PIECE[ordreJoueurs[1][20 - ordreJoueurs[1][20]]];
	  /**< piece disponible pour le joueur 2*/
	char score[10];
		/**< variable de recuperation des scores*/
	char tuiles[10];
		/**< variable de recuperation des nombres de tuiles*/
	float taille =
	    (largeurFenetre() >=
	     hauteurFenetre()) * largeurFenetre() / 6 + (hauteurFenetre() >
							 largeurFenetre()) *
	    hauteurFenetre() / 6;
		/**< taille des interfaces a afficher*/

	//Affiche le fond de l'application
	couleurCourante(78, 61, 40);
	rectangle(0, 0, largeurFenetre(), hauteurFenetre());

	//Fond interfaces des joueurs
	couleurCourante(247, 35, 12);
	rectangle(0, 0, taille, hauteurFenetre());
	couleurCourante(58, 242, 75);
	rectangle(largeurFenetre(), 0, largeurFenetre() - taille,
		  hauteurFenetre());

	//Affiche les noms des deux joueurs
	couleurCourante(240, 255, 255);
	epaisseurDeTrait(1);
	afficheChaine(nomJ1, taille / 6, taille / 10,
		      hauteurFenetre() - taille / 4);
	afficheChaine(nomJ2, taille / 6, largeurFenetre() - taille * 9 / 10,
		      hauteurFenetre() - taille / 4);

	//Affiche les scores des deux joueurs
	afficheChaine("Score :", taille / 6, taille / 10, taille / 2);
	sprintf(score, "%d", calculScore(1));
	afficheChaine(score, taille / 6, taille / 10, taille / 4);

	afficheChaine("Score : ", taille / 6,
		      largeurFenetre() - taille * 9 / 10, taille / 2);
	sprintf(score, "%d", calculScore(2));
	afficheChaine(score, taille / 6, largeurFenetre() - taille * 9 / 10,
		      taille / 4);

	//Affiche les tuiles restantes des deux joueurs
	afficheChaine("Tuiles :", taille / 6, taille / 10, taille);
	sprintf(tuiles, "%d", ordreJoueurs[0][20]);
	afficheChaine(tuiles, taille / 6, taille / 10, taille / 1.25);
	afficheChaine("Tuiles : ", taille / 6,
		      largeurFenetre() - taille * 9 / 10, taille);
	sprintf(tuiles, "%d", ordreJoueurs[1][20]);
	afficheChaine(tuiles, taille / 6,
		      largeurFenetre() - taille * 9 / 10, taille / 1.25);

	//Affiche les zones de sélection de tuile
	couleurCourante(78, 61, 40);
	rectangle(taille / 10, hauteurFenetre() * 2 / 3,
		  taille * 9 / 10,
		  (hauteurFenetre() * 2 / 3) - taille * 8 / 10);
	rectangle(largeurFenetre() - taille / 10,
		  hauteurFenetre() * 2 / 3,
		  largeurFenetre() - taille * 9 / 10,
		  (hauteurFenetre() * 2 / 3) - taille * 8 / 10);

	//Affiche les pièces disponibles

}

/**
 * \brief donne les coordonée dans le plateau des coordonnée de la soursi
 * \param [out]x abscisse de la casse ou la souris est
 * \param [out]y ordonnée de la casse ou la souris est
 * \param [in] zoom zoom de la grille
 * \return 1 si l'utilisateur a clique dans la grille
 * \return 0 si l'utilisateur à clique en dehors de la grille
 */
int detecteCase(int *x, int *y, int zoom, unsigned int basX, unsigned int basY)
{

	if (zoom < 1) {
		zoom = 1;
	}
	if (zoom >= TAILLEMAX) {
		zoom = TAILLEMAX - 1;
	}
	if (basX + zoom >= TAILLEMAX) {
		basX = (unsigned int)(TAILLEMAX - 1 - zoom);
	}
	if (basY + zoom >= TAILLEMAX) {
		basY = (unsigned int)(TAILLEMAX - 1 - zoom);
	}

	float largeur = largeurFenetre();
	float hauteur = hauteurFenetre();
	//Définit l'écart entre le centre de la fenêtre et le bord du plateau
	float ecart = (float)(((largeur <= hauteur) * largeur
			       + (largeur > hauteur) * hauteur) / 2.5);
	int abs = abscisseSouris();
	int ord = ordonneeSouris();
	//on regarde si l'utilisateur a cliqué dans la grille
	if (abs > (largeur / 2 - ecart) && abs < (largeur / 2 + ecart)
	    && ord < (hauteur / 2 + ecart)
	    && ord > (hauteur / 2 - ecart)) {
		float taille_case = 2 * ecart / zoom;
		*x = (int)(((abs + ecart - largeur / 2) / taille_case) + basX);
		*y = (int)(((ord + ecart - hauteur / 2) / taille_case) + basY);
		return 1;
	}
	*x = -1;
	*y = -1;
	return 0;
}

/*!
 * \brief trouve le meilleur zooom pour le cadrage actuelle
 * \param [out] x pointeur vers l'abscisse du meilleur zoom
 * \param [out] y pointeur vers l'ordonnée du meilleur zoom
 * \param [out] zoom pointeur vers le meilleur zoom
 * \return -1 en cas d'erreur
 * \return 0 si non
 */
int trouveMeilleurZoom(unsigned int *x, unsigned int *y, unsigned int *zoom)
{
	int x_min = 0, x_max = 0, y_min = 0, y_max = 0;
	int i = 0, j = 0;
	int zoomTmp;
	bool haut = true, bas = true, gauche = true, droite = true;
	//tant que les coordonnés du point le plus en bas à droite et celui en haut à gauche n'ont pas été trouvée
	while (haut || bas || droite || gauche) {
		if (gauche && vide != getCouleurCase(*getCase(i, j))) {
			y_min = j;
			gauche = false;
		}
		if (bas && vide != getCouleurCase(*getCase(j, i))) {
			x_min = j;
			bas = false;
		}
		if (droite && vide != getCouleurCase(*getCase(TAILLEMAX - i - 1,
							      TAILLEMAX - j -
							      1))) {
			y_max = TAILLEMAX - j - 1;
			droite = false;
		}
		if (haut && vide !=
		    getCouleurCase(*getCase
				   (TAILLEMAX - j - 1, TAILLEMAX - i - 1))) {
			x_max = TAILLEMAX - j - 1;
			haut = false;
		}
		i += 1;
		if (i == TAILLEMAX) {
			i = 0;
			j += 1;
			//si j vaut taille max, la tableau est vide ou il y a eu une erreur
			if (j == TAILLEMAX) {
				puts("erreur dans la detection du zoom");
				return -1;
			}
		}
	}
	//on laisse, si possible une marge de 2 carreau
	x_min = x_min - 2;
	y_min = y_min - 2;
	y_max = y_max + 2;
	x_max = x_max + 2;
	//mise en place des plancher(0) et des saturation (TAILLEMAX-1) des valeurs
	x_min = (x_min > 0) ? x_min : 0;
	y_min = (y_min > 0) ? y_min : 0;
	y_max = (y_max < TAILLEMAX) ? y_max : TAILLEMAX - 1;
	x_max = (x_max < TAILLEMAX) ? x_max : TAILLEMAX - 1;
	//le zoom vaut l'ecart maximum entre les abscisse ou les ordonnée
	if ((x_max - x_min) > (y_max - y_min)) {
		zoomTmp = (x_max - x_min) + 1;
		y_min = y_min - ((zoomTmp - (y_max - y_min)) / 2);
		y_min = (y_min > 0) ? y_min : 0;
	} else {
		zoomTmp = (y_max - y_min) + 1;
		x_min = x_min - ((zoomTmp - (x_max - x_min)) / 2);
		x_min = (x_min > 0) ? x_min : 0;
	}
	*y = (unsigned int)y_min;
	*x = (unsigned int)x_min;
	*zoom = (unsigned int)zoomTmp;
	return 0;
}
