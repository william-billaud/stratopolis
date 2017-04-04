/*!
* \file affichage.c
* \brief fichier contenant les fonctions d'affichages
* \author billaud et hipault
* \date 22/01/17
*/

#include "affichage.h"

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
	float ecart = (((largeur <= hauteur) * largeur
			+ (largeur > hauteur) * hauteur) / 2.5f);
	float taille_case = 2 * ecart / zoom;
	float minX, minY, maxX, maxY;

	//Affiche une bordure du plateau de 5 pixels
	couleurCourante(38, 21, 0);
	rectangle(largeur / 2 - ecart - 5,
		  hauteur / 2 - ecart - 5,
		  largeur / 2 + ecart + 5, hauteur / 2 + ecart + 5);

	//Parcours du plateu de jeu
	unsigned int i;
	unsigned int j;
	for (i = (basX); i < (basX + zoom); i++) {
		for (j = (basY); j < (basY + zoom); j++) {

			minX = largeur / 2 - ecart + (i - basX) * taille_case;
			minY = hauteur / 2 - ecart + (j - basY) * taille_case;
			maxX = largeur / 2 - ecart + (i - basX +
						      1) * taille_case;
			maxY = hauteur / 2 - ecart + (j - basY +
						      1) * taille_case;

			//Affiche la case
			afficheCase((couleur) getCouleurCase(getCase(i, j)),
				    getHauteurCase(getCase(i, j)), minX, minY,
				    maxX, maxY, false);

			//Affiche les bordures
			afficheBorduresDeCase(getNumeroPiece(getCase(i, j)),
					      getNumeroPiece(getCase(i, j + 1)),
					      getNumeroPiece(getCase(i + 1, j)),
					      getNumeroPiece(getCase(i, j - 1)),
					      getNumeroPiece(getCase(i - 1, j)),
					      minX + (maxX - minX) / 2,
					      minY + (maxY - minY) / 2,
					      taille_case);
		}
	}
}

/**
  * \brief Affiche une case d'une pièce
  * \param [in] numeroPiece : numero de la pièce à afficher
  * \param [in] orientationPiece : orientation de la pièce
  * \param [in] minX : coordonnee minimum en abscisse où afficher la pièce
  * \param [in] minY : coordonnee minimum en ordonnée
  * \param [in] maxX : coordonnee maximum en abscisse
  * \param [in] maxY : coordonnee maximum en ordonée
	* \param [in] estGrisee : determine si la case doit être grisée (true) ou non (false)
   */
void affichePiece(int numeroPiece, orientation orientationPiece, int minX,
		  int minY, int maxX, int maxY, bool estGrisee)
{
	pieces maPiece = PIECE[numeroPiece];
	couleur hautGauche, hautDroite, basDroite, basGauche;
	float centreX, centreY;
	if (orientationPiece == BD) {
		hautGauche = maPiece.c2;
		hautDroite = maPiece.c1;
		basGauche = maPiece.c3;
		basDroite = vide;
	} else if (orientationPiece == HG) {
		hautGauche = vide;
		hautDroite = maPiece.c3;
		basGauche = maPiece.c1;
		basDroite = maPiece.c2;
	} else if (orientationPiece == BG) {
		hautGauche = maPiece.c3;
		hautDroite = maPiece.c2;
		basGauche = vide;
		basDroite = maPiece.c1;
	} else {
		hautGauche = maPiece.c1;
		hautDroite = vide;
		basGauche = maPiece.c2;
		basDroite = maPiece.c3;
	}

	centreX = maxX - (maxX - minX) / 2;
	centreY = maxY - (maxX - minX) / 2;

	if (hautGauche != vide) {
		afficheCase(hautGauche, 0, minX, centreY, centreX, maxY,
			    estGrisee);
	}
	if (hautDroite != vide) {
		afficheCase(hautDroite, 0, centreX, centreY, maxX, maxY,
			    estGrisee);
	}
	if (basGauche != vide) {
		afficheCase(basGauche, 0, minX, minY, centreX, centreY,
			    estGrisee);
	}
	if (basDroite != vide) {
		afficheCase(basDroite, 0, centreX, minY, maxX, centreY,
			    estGrisee);
	}
}

/**
 * \brief Affiche une case d'une pièce
 * \param [in] couleurCase : couleur de la case à afficher
 * \param [in] hauteurCase : hauteur de la case à afficher
 * \param [in] minX : coordonnee minimum en abscisse où afficher la case
 * \param [in] minY : coordonnee minimum en ordonnée
 * \param [in] maxX : coordonnee maximum en abscisse
 * \param [in] maxY : coordonnee maximum en ordonée
 * \param [in] estGrisee : determine si la case doit être grisée (true) ou non (false)
   */
void afficheCase(couleur couleurCase, int hauteurCase, float minX,
		 float minY, float maxX, float maxY, bool estGrisee)
{
	char hauteur[20];
	int marge = 3;

	//Trace le contour
	couleurCourante(58, 41, 20);
	rectangle(minX + 1, minY + 1, maxX - 1, maxY - 1);

	//Determine la couleur de la case
	determineCouleur(couleurCase, estGrisee);

	//Trace la case
	rectangle(minX + marge, minY + marge, maxX - marge, maxY - marge);

	//Affiche la hauteur de la case
	if (couleurCase != vide && hauteurCase > 0) {
		sprintf(hauteur, "%d", hauteurCase);
		couleurCourante(240, 255, 255);
		epaisseurDeTrait(2);
		afficheChaine(hauteur, (maxX - minX) / 4,
			      minX +
			      tailleChaine(hauteur,
					   maxX - minX),
			      (float)(minY + (maxX - minX) / 4.5));
	}
}

/*!
 * \brief appelle couleurCourante() en fonction du paramètre
 * \param [in] couleurCase couleur de la case à déterminer
 * \param [in] estGrisee : determine si la couleur doit être grisée (true) ou non (false)
 * \return rien
 */
void determineCouleur(couleur couleurCase, bool estGrisee)
{
	switch (couleurCase) {
	case neutre:
		couleurCourante(135, 87, 39);
		if (estGrisee) {
			couleurCourante(50, 30, 0);
		}
		break;
	case rouge:
		couleurCourante(247, 35, 12);
		if (estGrisee) {
			couleurCourante(50, 0, 0);
		}
		break;
	case vert:
		couleurCourante(58, 242, 75);
		if (estGrisee) {
			couleurCourante(0, 50, 0);
		}
		break;
	case vide:
		couleurCourante(78, 61, 40);
		break;
	}
}

/**
 * \brief Affiche les contours d'une case
 * \param [in] numC : numéro de la case
 * \param [in] numH : numéro de la case du haut
 * \param [in] numD : numéro de la case de droite
 * \param [in] numB : numéro de la case du bas
 * \param [in] numG : numéro de la case de gauche
 * \param [in] centreY : coordonnee en ordonnee du centre de la case
 * \param [in] centreX : coordonnee en abscisse du centre de la case
 * \param [in] taille_case : taille des cases
  */
void afficheBorduresDeCase(int numC, int numH, int numD, int numB, int numG,
			   float centreX, float centreY, float taille_case)
{
	//Case de droite
	afficheBordureEntreCases(numC, numD, centreX, centreY,
				 centreX + taille_case, centreY);
	//Case de gauche
	afficheBordureEntreCases(numC, numG,
				 centreX, centreY,
				 centreX - taille_case, centreY);
	//Case du haut
	afficheBordureEntreCases(numC, numH,
				 centreX, centreY,
				 centreX, centreY + taille_case);
	//Case du bas
	afficheBordureEntreCases(numC, numB,
				 centreX, centreY,
				 centreX, centreY - taille_case);
}

/**
 * \brief Affiche la séparation entre deux cases de pièces différentes
 * \param [in] numero1 : numéro de la première pièce
 * \param [in] numero2 : numéro de la deuxième pièce
 * \param [in] centreX1 : coordonnee en abscisse du centre de la première case
 * \param [in] centreY1 : coordonnee en ordonnee du centre de la première case
 * \param [in] centreX2 : coordonnee en abscisse du centre de la deuxième case
 * \param [in] centreX2 : coordonnee en ordonnee du centre de la deuxième case
  */
void afficheBordureEntreCases(int numero1, int numero2, float centreX1,
			      float centreY1, float centreX2, float centreY2)
{
	float minX, minY, maxX, maxY, taille;
	minX =
	    (centreX1 <= centreX2) * centreX1 + (centreX2 <
						 centreX1) * centreX2;
	maxX =
	    (centreX1 >= centreX2) * centreX1 + (centreX2 >
						 centreX1) * centreX2;
	minY =
	    (centreY1 <= centreY2) * centreY1 + (centreY2 <
						 centreY1) * centreY2;
	maxY =
	    (centreY1 >= centreY2) * centreY1 + (centreY2 >
						 centreY1) * centreY2;
	taille = (maxX - minX + maxY - minY) / 2;
	if (numero1 != numero2) {
		epaisseurDeTrait(2);
		couleurCourante(100, 100, 100);
		//Cas horizontal
		if ((maxY - minY) == 0) {
			ligne(minX + taille, minY + taille, minX + taille,
			      minY - taille);
		}
		//Cas vertical
		else {
			ligne(minX + taille, minY + taille, minX - taille,
			      minY + taille);
		}
	}
}

/*!
   \brief Affiche l’interface de jeu
   \param[in] nomJ1 : nom du premier joueur
	 \param[in] nomJ2 : nom du deuxième joueur
	 \return rien
*/
void afficheInterface(char nomJ1[15], char nomJ2[15], int joueurActuelle)
{
	pieces pieceJ1 = PIECE[ordreJoueurs[0][ordreJoueurs[0][20]]];
    /**< piece disponible pour le joueur 1*/
	pieces pieceJ2 = PIECE[ordreJoueurs[1][ordreJoueurs[1][20]]];
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

	determineCouleur(rouge, (bool) joueurActuelle);
	rectangle(0, 0, taille, hauteurFenetre());
	determineCouleur(vert, (bool) ((joueurActuelle + 1) % 2));
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
	sprintf(score, "%d", calculScore(0));
	afficheChaine(score, taille / 6, taille / 10, taille / 4);

	afficheChaine("Score : ", taille / 6,
		      largeurFenetre() - taille * 9 / 10, taille / 2);
	sprintf(score, "%d", calculScore(1));
	afficheChaine(score, taille / 6, largeurFenetre() - taille * 9 / 10,
		      taille / 4);

	//Affiche les tuiles restantes des deux joueurs
	afficheChaine("Tuiles :", taille / 6, taille / 10, taille);
	sprintf(tuiles, "%d", 20 - ordreJoueurs[0][20]);
	afficheChaine(tuiles, taille / 6, taille / 10, (taille / 1.25f));
	afficheChaine("Tuiles : ", taille / 6,
		      largeurFenetre() - taille * 9 / 10, taille);
	sprintf(tuiles, "%d", 20 - ordreJoueurs[1][20]);
	afficheChaine(tuiles, taille / 6,
		      largeurFenetre() - taille * 9 / 10, (taille / 1.25f));

	//Affiche les zones de sélection de tuile
	float x_min = taille / 10;
	float x_max = taille * 9 / 10;
	float y_max = hauteurFenetre() * 2 / 3;
	float y_min = y_max - taille * 8 / 10;
	float marge = taille / 10;

	couleurCourante(200, 200, 200);
	rectangle(x_min, y_min, x_max, y_max);
	rectangle(largeurFenetre() - x_min, y_min, largeurFenetre() - x_max,
		  y_max);
	affichePiece(pieceJ1.numeroPiece, HD, (int)(x_min + marge),
		     (int)(y_min + marge), (int)(x_max - marge),
		     (int)(y_max - marge), false);
	affichePiece(pieceJ2.numeroPiece, HD,
		     (int)(largeurFenetre() - x_max + marge),
		     (int)(y_min + marge),
		     (int)(largeurFenetre() - x_min - marge),
		     (int)(y_max - marge), false);
	afficheDuree(taille);
}

/*!
   \brief Appelle les fonction dessinePredictif() et estValideCoup()
   \param[in] coupJoueur : coup à afficher
   \return rien
*/
void affichePredictif(coup coupJoueur, int zoom)
{
	dessinePredictif(coupJoueur, estValideCoup(coupJoueur), zoom);
}

/*!
   \brief Affiche le prédictif de placement de la pièce
   \param[in] coupJoueur : coup à afficher
	 \param[in] estValide : validité du coup à afficher
   \return
*/
void dessinePredictif(coup coupJoueur, bool estValide, int zoom)
{
	float taille =
	    (float)(2 *
		    (((largeurFenetre() <= hauteurFenetre()) * largeurFenetre()
		      + (largeurFenetre() >
			 hauteurFenetre()) * hauteurFenetre()) / 2.5) / zoom);

	float minX, minY, maxX, maxY;
	if (coupJoueur.orientationPiece == BD) {
		minX = abscisseSouris() - taille / 2;
		minY = ordonneeSouris() - taille * 3 / 2;
		maxX = abscisseSouris() + taille * 3 / 2;
		maxY = ordonneeSouris() + taille / 2;
	} else if (coupJoueur.orientationPiece == BG) {
		minX = abscisseSouris() - taille * 3 / 2;
		minY = ordonneeSouris() - taille * 3 / 2;
		maxX = abscisseSouris() + taille / 2;
		maxY = ordonneeSouris() + taille / 2;
	} else if (coupJoueur.orientationPiece == HG) {
		minX = abscisseSouris() - taille * 3 / 2;
		minY = ordonneeSouris() - taille / 2;
		maxX = abscisseSouris() + taille / 2;
		maxY = ordonneeSouris() + taille * 3 / 2;
	} else {
		minX = abscisseSouris() - taille / 2;
		minY = ordonneeSouris() - taille / 2;
		maxX = abscisseSouris() + taille * 3 / 2;
		maxY = ordonneeSouris() + taille * 3 / 2;
	}
	affichePiece(coupJoueur.numeroPiece, coupJoueur.orientationPiece,
		     (int)minX, (int)minY, (int)maxX, (int)maxY, !estValide);
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
	    && ord < (hauteur / 2 + ecart) && ord > (hauteur / 2 - ecart)) {
		float taille_case = 2 * ecart / zoom;
		*x = (int)(((abs + ecart - largeur / 2) / taille_case) + basX);
		*y = (int)(((ord + ecart - hauteur / 2) / taille_case) + basY);
		return 1;
	}
	*x = -1;
	*y = -1;
	return 0;
}

void changeZoom(unsigned int *x_z, unsigned int *y_z, unsigned int *zoom,
		bool up)
{
	int x_c, y_c;
	int b = up ? -1 : 1;
	if ((*zoom > 1 || !up) && (*zoom < TAILLEMAX || up)) {
		if (detecteCase(&x_c, &y_c, *zoom, *x_z, *y_z) == 1) {
			if (up) {
				y_c =
				    (y_c >
				     (int)(*y_z + (*zoom) / 2)) ? (*y_z) +
				    2 : (*y_z);
				x_c =
				    (x_c >
				     (int)(*x_z + (*zoom) / 2)) ? (*x_z) +
				    2 : (*x_z);
			} else {
				y_c =
				    (y_c >
				     (int)(*y_z + (*zoom) / 2)) ? (*y_z) -
				    2 : (*y_z);
				x_c =
				    (x_c >
				     (int)(*x_z + (*zoom) / 2)) ? (*x_z) -
				    2 : (*x_z);

			}
			*zoom += b;
			printf("%d, %d\n", x_c, y_c);
			*x_z = (unsigned int)x_c;
			*y_z = (unsigned int)y_c;
		}
	}
}

void afficheDuree(int taille)
{
	char chaine[20];
	int dure = (int)(time(NULL) - timeStart);
	int H = dure / 3600;
	int m = (dure - H * 3600) / 60;
	int s = (dure - H * 3600 - m * 60);
	sprintf(chaine, "%.2dh%.2dm%.2ds", H, m, s);
	epaisseurDeTrait(1);
	couleurCourante(240, 255, 255);
	epaisseurDeTrait(1);
	afficheChaine(chaine, taille / 10, 2 * largeurFenetre() / 3,
		      hauteurFenetre() - taille / 4);;

}
