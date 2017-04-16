/*!
* \file affichage.c
* \brief fichier contenant les fonctions d'affichages
* \author billaud et hipault
* \date 22/01/17
*/

#include "affichage.h"

/*!
 * \brief Affiche le menu principal (Jouer, Aide, Options, Quitter), et la sélection
 * \return rien
 */
void afficheMenu() {

    float tailleBoutonX = largeurFenetre() / 10;
    float tailleBoutonY = hauteurFenetre() / 20;
    float centreX = largeurFenetre() / 2;
    float centreY = hauteurFenetre() / 2;

    static DonneesImageRGB *img_boite = NULL;
    static DonneesImageRGB *img_plateau = NULL;
    static DonneesImageRGB *img_logo = NULL;
    if (img_boite == NULL) {
        img_boite = lisBMPRGB("./ressources/boite.bmp");
    }
    if (img_plateau == NULL) {
        img_plateau = lisBMPRGB("./ressources/plateau.bmp");
    }
    if (img_logo == NULL) {
        img_logo = lisBMPRGB("./ressources/logo.bmp");
    }
    if (img_logo != NULL && img_plateau != NULL && img_boite != NULL) {
        if (largeurFenetre() >= 650 && hauteurFenetre() >= 400) {
            ecrisImage((int) (centreX - tailleBoutonX - img_plateau->largeurImage), 0, img_plateau->largeurImage,
                       img_plateau->hauteurImage, img_plateau->donneesRGB);
            ecrisImage((int) (centreX + tailleBoutonX + 5), hauteurFenetre() - img_boite->hauteurImage,
                       img_boite->largeurImage, img_boite->hauteurImage, img_boite->donneesRGB);

        }
        ecrisImage((int) (centreX - (img_logo->largeurImage / 2)),
                   (int) ((hauteurFenetre() - img_logo->hauteurImage) / 1.07), img_logo->largeurImage,
                   img_logo->hauteurImage, img_logo->donneesRGB);
    }

    (detecteMenuPrincipal() == 1) ? couleurCourante(231, 62, 1) : couleurCourante(255, 0, 0);
    rectangle(centreX - tailleBoutonX, centreY + 2 * tailleBoutonY,
              centreX + tailleBoutonX, centreY + 4 * tailleBoutonY);
    (detecteMenuPrincipal() == 2) ? couleurCourante(231, 62, 1) : couleurCourante(255, 0, 0);
    rectangle(centreX - tailleBoutonX, centreY - tailleBoutonY,
              centreX + tailleBoutonX, centreY + tailleBoutonY);
    (detecteMenuPrincipal() == 3) ? couleurCourante(231, 62, 1) : couleurCourante(255, 0, 0);
    rectangle(centreX - tailleBoutonX, centreY - 2 * tailleBoutonY,
              centreX + tailleBoutonX, centreY - 4 * tailleBoutonY);
    (detecteMenuPrincipal() == 4) ? couleurCourante(231, 62, 1) : couleurCourante(255, 0, 0);
    rectangle(centreX - tailleBoutonX, centreY - 5 * tailleBoutonY,
              centreX + tailleBoutonX, centreY - 7 * tailleBoutonY);

    couleurCourante(200, 200, 200);
    epaisseurDeTrait(4);
    afficheChaine("JOUER", 24, centreX - tailleChaine("JOUER", 24) / 2,
                  centreY + 2 * tailleBoutonY + tailleBoutonY * 3 / 5);
    afficheChaine("OPTIONS", 24, centreX - tailleChaine("OPTION", 24) / 2,
                  centreY - tailleBoutonY + tailleBoutonY * 3 / 5);
    afficheChaine("AIDE", 24, centreX - tailleChaine("AIDE", 24) / 2,
                  centreY - 4 * tailleBoutonY + tailleBoutonY * 3 / 5);
    afficheChaine("QUITTER", 24, centreX - tailleChaine("QUITTER", 24) / 2,
                  centreY - 7 * tailleBoutonY + tailleBoutonY * 3 / 5);
}

/*!
 * \brief Affiche le menu de sélection des options, et la sélection
 * \param[in] limiteTemp indique si la limite de temp est activée
 * \param[in] dureeLimite indique la durée maximum d'un tour
 * \param[in] niveauDifficulte indique le niveau de difficulté (entre 0 et 4)
 * \param[in] modeSuivant indique le mode de jeu actuel
 * \return rien
 */
void afficheOption(bool limiteTemp, unsigned int dureeLimite, int niveauDifficulte, int modeSuivant) {
    float tailleBoutonX = largeurFenetre() / 6;
    float tailleBoutonY = hauteurFenetre() / 20;
    float centreX = largeurFenetre() / 2;
    float centreY = hauteurFenetre() / 2;

    char limite[15];
    char difficulte[15];
    char modeOption[20];

    effaceFenetre(0, 0, 0);

    (detecteMenuOption() == 1) ? couleurCourante(231, 62, 1) : couleurCourante(255, 0, 0);
    rectangle(centreX / 2 - tailleBoutonX, centreY + 2 * tailleBoutonY,
              centreX / 2 + tailleBoutonX, centreY + 4 * tailleBoutonY);

    (detecteMenuOption() == 3) ? couleurCourante(231, 62, 1) : couleurCourante(255, 0, 0);
    if (modeSuivant == 1) {
        couleurCourante(125, 125, 125);
    }
    rectangle(centreX / 2 - tailleBoutonX, centreY - 3 * tailleBoutonY,
              centreX / 2 + tailleBoutonX, centreY - 5 * tailleBoutonY);

    (detecteMenuOption() == 2) ? couleurCourante(231, 62, 1) : couleurCourante(255, 0, 0);
    if (modeSuivant == 2) {
        couleurCourante(125, 125, 125);
    }
    rectangle(3 * centreX / 2 - tailleBoutonX, centreY + 2 * tailleBoutonY,
              3 * centreX / 2 + tailleBoutonX, centreY + 4 * tailleBoutonY);

    (detecteMenuOption() == 4) ? couleurCourante(231, 62, 1) : couleurCourante(255, 0, 0);
    rectangle(3 * centreX / 2 - tailleBoutonX, centreY - 3 * tailleBoutonY,
              3 * centreX / 2 + tailleBoutonX, centreY - 5 * tailleBoutonY);

    (detecteMenuOption() == 5) ? couleurCourante(231, 62, 1) : couleurCourante(255, 0, 0);
    rectangle(0, 0, tailleBoutonX, 2 * tailleBoutonY);

    couleurCourante(200, 200, 200);
    epaisseurDeTrait(3);
    afficheChaine("OPTIONS", 50, centreX - tailleChaine("OPTIONS", 50) / 2, hauteurFenetre() - 3 * tailleBoutonY);
    afficheChaine("Mode de jeu", 24, centreX / 2 - tailleChaine("Mode de jeu", 24) / 2,
                  centreY + 5 * tailleBoutonY);
    afficheChaine("Difficulte IA", 24, centreX / 2 - tailleChaine("Difficulte IA", 24) / 2,
                  centreY - 2 * tailleBoutonY);
    afficheChaine("Limite de temps", 24, 3 * centreX / 2 - tailleChaine("Limite de temps", 24) / 2,
                  centreY + 5 * tailleBoutonY);


    afficheChaine("Changer noms", 24, 3 * centreX / 2 - tailleChaine("Changer noms", 24) / 2,
                  centreY - 5 * tailleBoutonY + tailleBoutonY * 3 / 5);
    afficheChaine("Retour", 24, tailleBoutonX / 2 - tailleChaine("Retour", 24) / 2, tailleBoutonY * 3 / 5);

    if (!limiteTemp) {
        sprintf(limite, "%s", "Aucune");
    } else {
        sprintf(limite, "%d %s", dureeLimite, "secondes");
    }
    afficheChaine(limite, 24, 3 * centreX / 2 - tailleChaine(limite, 24) / 2,
                  centreY + 2 * tailleBoutonY + tailleBoutonY * 3 / 5);


    switch (niveauDifficulte) {
        case 0:
            sprintf(difficulte, "%s", "Facile");
            break;
        case 1:
            sprintf(difficulte, "%s", "Moyen");
            break;
        case 2:
            sprintf(difficulte, "%s", "Dur");
            break;
        case 3:
            sprintf(difficulte, "%s", "Tres dur");
            break;
        case 4:
            sprintf(difficulte, "%s", "Extreme");
            break;
        default:
            sprintf(difficulte, "%s", "Erreur");
            break;
    }
    afficheChaine(difficulte, 24, centreX / 2 - tailleChaine(difficulte, 24) / 2,
                  centreY - 5 * tailleBoutonY + tailleBoutonY * 3 / 5);

    if (modeSuivant == 2) {
        sprintf(modeOption, "%s", "Joueur VS IA");
    } else {
        sprintf(modeOption, "%s", "Joueur VS Joueur");
    }

    afficheChaine(modeOption, 24, centreX / 2 - tailleChaine(modeOption, 24) / 2,
                  centreY + 2 * tailleBoutonY + tailleBoutonY * 3 / 5);

}

/*!
 * \brief Affiche les règles du jeu et le mode d’emploi du programme, et la sélection
 * \return rien
 */
void afficheAide(void) {
    float centreX = largeurFenetre() / 2;
    float centreY = hauteurFenetre() / 2;
    static DonneesImageRGB *img_reglesPetit = NULL;
    static DonneesImageRGB *img_reglesMoyen = NULL;
    static DonneesImageRGB *img_reglesGrand = NULL;
    if (img_reglesPetit == NULL ) {
        img_reglesPetit = lisBMPRGB("./ressources/regles400x320.bmp");
    }
    if (img_reglesMoyen == NULL) {
        img_reglesMoyen = lisBMPRGB("./ressources/regles600x480.bmp");
    }
    if (img_reglesGrand == NULL) {
        img_reglesGrand = lisBMPRGB("./ressources/regles750x600.bmp");
    }

    if (img_reglesPetit != NULL && (largeurFenetre() < 600 || hauteurFenetre() < 480)) {
        ecrisImage((int) (centreX - img_reglesPetit->largeurImage / 2),
                   (int) (centreY - img_reglesPetit->hauteurImage / 2),
                   img_reglesPetit->largeurImage,
                   img_reglesPetit->hauteurImage, img_reglesPetit->donneesRGB);
    } else if (img_reglesMoyen != NULL && (largeurFenetre() < 750|| hauteurFenetre() < 600)) {
        ecrisImage((int) (centreX - img_reglesMoyen->largeurImage / 2),
                   (int) (centreY - img_reglesMoyen->hauteurImage / 2),
                   img_reglesMoyen->largeurImage,
                   img_reglesMoyen->hauteurImage, img_reglesMoyen->donneesRGB);
    } else if (img_reglesGrand != NULL && largeurFenetre() >= 750 && hauteurFenetre() >= 600) {
        ecrisImage((int) (centreX - img_reglesGrand->largeurImage / 2),
                   (int) (centreY - img_reglesGrand->hauteurImage / 2),
                   img_reglesGrand->largeurImage,
                   img_reglesGrand->hauteurImage, img_reglesGrand->donneesRGB);
    }
}

/*!
 * \brief affiche le joueur gagnant et son score
 * \param[in] scoreGagnant score du gagnant
 * \param[in] scorePerdant score du perdant
 * \param[in] joueurGagnant nom du joueur gagnant
 * \return rien
 */
void afficheVictoire(int scoreGagnant, int scorePerdant, char joueurGagnant[15]) {
    static bool chgmtCouleur = true;
    static unsigned int timerChgmtCouleur = 0;
    static float positionX = 0;
    float nb_rectangles = 20;
    float taille = largeurFenetre() / nb_rectangles;
    float minX, maxX;
    char score[40];
    char gagnant[30];
    unsigned int i;

    if (chgmtCouleur) {
        effaceFenetre(78, 61, 40);
        couleurCourante(58, 242, 75);
    } else {
        effaceFenetre(78, 61, 40);
        couleurCourante(247, 35, 12);
    }
    rectangle(positionX - taille, 0, positionX - 2 * taille, taille);
    rectangle(positionX - taille, taille, positionX, 2 * taille);
    rectangle(largeurFenetre() - positionX + taille, hauteurFenetre() - taille,
              largeurFenetre() - positionX + 2 * taille, hauteurFenetre());
    for (i = 0; i <= nb_rectangles; i += 2) {
        minX = positionX + i * taille;
        maxX = positionX + i * taille + taille;
        rectangle(minX, 0, maxX, taille);
        minX = positionX + (i - 1) * taille;
        maxX = positionX + (i - 1) * taille + taille;
        rectangle(minX, taille, maxX, 2 * taille);
        minX = largeurFenetre() - positionX - (i + 1) * taille;
        maxX = largeurFenetre() - positionX - (i + 1) * taille + taille;
        rectangle(minX, hauteurFenetre() - taille, maxX, hauteurFenetre());
        minX = largeurFenetre() - positionX - i * taille;
        maxX = largeurFenetre() - positionX - i * taille + taille;
        rectangle(minX, hauteurFenetre() - 2 * taille, maxX, hauteurFenetre() - taille);
    }

    couleurCourante(200, 200, 200);
    rectangleVide(2, 2 * taille + 1, largeurFenetre() - 2, hauteurFenetre() - 2 * taille - 1, 5);

    sprintf(score, "Score  : %d a %d", scoreGagnant, scorePerdant);
    sprintf(gagnant, "%s a gagne !", joueurGagnant);
    epaisseurDeTrait(5);
    afficheChaine(score, 50, largeurFenetre() / 2 - tailleChaine(score, 50) / 2, hauteurFenetre() / 3);
    afficheChaine(gagnant, 50, largeurFenetre() / 2 - tailleChaine(gagnant, 50) / 2, hauteurFenetre() / 2);

    timerChgmtCouleur++;
    positionX += 2;
    if (positionX > 2 * taille) {
        positionX = 0;
    }
    if (timerChgmtCouleur > 50) {
        timerChgmtCouleur = 0;
        chgmtCouleur = !chgmtCouleur;
    }
}

/*!
 * \brief Affiche le plateau de jeu, la couleur et la hauteur de chaque case
 * \param[in] zoom : nombre de case affiché par ligne/colonne
 * \param[in] basX : abscisse de la case du bas
 * \param[in] basY : abscisse de la case du bas
 */
void afficheGrille(unsigned int zoom, unsigned int basX, unsigned int basY) {
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

/*!
  * \brief Affiche une case d'une pièce
  * \param [in] numeroPiece : numero de la pièce à afficher
  * \param [in] orientationPiece : orientation de la pièce
  * \param [in] minX : coordonnee minimum en abscisse où afficher la case
  * \param [in] minY : coordonnee minimum en ordonnée
  * \param [in] maxX : coordonnee maximum en abscisse
  * \param [in] maxY : coordonnee maximum en ordonée
  * \param [in] estGrisee : determine si la case doit être grisée (true) ou non (false)
   */
void affichePiece(int numeroPiece, orientation orientationPiece, int minX,
                  int minY, int maxX, int maxY, bool estGrisee) {
    if (numeroPiece < 0 || numeroPiece > 40) {
        return;
    }
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

/*!
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
                 float minY, float maxX, float maxY, bool estGrisee) {
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
                      (float) (minY + (maxX - minX) / 4.5));
    }
}

/*!
 * \brief appelle couleurCourante() en fonction du paramètre
 * \param [in] couleurCase : couleur de la case à déterminer
 * \param [in] estGrisee : determine si la couleur doit être grisée (true) ou non (false)
 * \return rien
 */
void determineCouleur(couleur couleurCase, bool estGrisee) {
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

/*!
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
                           float centreX, float centreY, float taille_case) {
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

/*!
 * \brief Affiche la séparation entre deux cases de pièces différentes
 * \param [in] numero1 : numéro de la première case
 * \param [in] numero2 : numéro de la deuxième case
 * \param [in] centreX1 : coordonnee en abscisse du centre de la première case
 * \param [in] centreY1 : coordonnee en ordonnee du centre de la première case
 * \param [in] centreX2 : coordonnee en abscisse du centre de la deuxième case
 * \param [in] centreY2 : coordonnee en ordonnee du centre de la deuxième case
  */
void afficheBordureEntreCases(int numero1, int numero2, float centreX1,
                              float centreY1, float centreX2, float centreY2) {
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
 * \brief Affiche l’interface de jeu
 * \param[in] nomJ1 : nom du premier joueur
 * \param[in] nomJ2 : nom du deuxième joueur
 * \param[in] joueurActuelle : joueur dont c'est le tour
 * \return rien
 */
void afficheInterface(char nomJ1[15], char nomJ2[15], int joueurActuelle) {
    pieces pieceJ1;
    pieces pieceJ2;
    float tailleC;
    if (ordreJoueurs[0][20] < 0 || ordreJoueurs[0][20] > 19) {
        pieceJ1.numeroPiece = 42;

    } else {
        pieceJ1 = PIECE[ordreJoueurs[0][ordreJoueurs[0][20]]];
        /**< piece disponible pour le joueur 1*/
    }
    if (ordreJoueurs[1][20] < 0 || ordreJoueurs[1][20] > 19) {
        pieceJ2.numeroPiece = 42;

    } else {
        pieceJ2 = PIECE[ordreJoueurs[1][ordreJoueurs[1][20]]];
        /**< piece disponible pour le joueur 2*/
    }

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
    //regle la taille d'affichage des noms
    tailleC = taille / 6;
    while (tailleChaine(nomJ1, tailleC) > 0.9 * taille) {
        tailleC = tailleC - 2;
    }
    afficheChaine(nomJ1, tailleC, taille / 10,
                  hauteurFenetre() - taille / 4);
    tailleC = taille / 6;
    while (tailleChaine(nomJ2, tailleC) > 0.9 * taille) {
        tailleC = tailleC - 2;
    }
    afficheChaine(nomJ2, tailleC, largeurFenetre() - taille * 9 / 10,
                  hauteurFenetre() - taille / 4);

    afficheScore(calculScore(0), calculScore(1));
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
    affichePiece(pieceJ1.numeroPiece, HD, (int) (x_min + marge),
                 (int) (y_min + marge), (int) (x_max - marge),
                 (int) (y_max - marge), false);
    affichePiece(pieceJ2.numeroPiece, HD,
                 (int) (largeurFenetre() - x_max + marge),
                 (int) (y_min + marge),
                 (int) (largeurFenetre() - x_min - marge),
                 (int) (y_max - marge), false);
    afficheDuree((int) taille);
}

/*!
 * \brief Appelle les fonction dessinePredictif() et estValideCoup()
 * \param[in] coupJoueur : coup à afficher
 * \param[in] zoom de la grille
 * \return rien
 */
void affichePredictif(coup coupJoueur, int zoom) {
    dessinePredictif(coupJoueur, estValideCoup(coupJoueur), zoom);
}

/*!
 * \brief Affiche le prédictif de placement de la pièce
 * \param[in] coupJoueur : coup à afficher
 * \param[in] estValide : validité du coup à afficher
 * \param[in] zoom zoom de la grille
 * \return
	*/
void dessinePredictif(coup coupJoueur, bool estValide, int zoom) {
    float taille =
            (float) (2 *
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
                 (int) minX, (int) minY, (int) maxX, (int) maxY, !estValide);
}

/*!
 * \brief donne les coordonées dans le plateau des coordonnée de la souris
 * \param[out] x : abscisse de la casse ou la souris est
 * \param[out] y : ordonnée de la casse ou la souris est
 * \param[in] zoom : zoom de la grille
 * \param[in] basX : plus petite abscisse affichée
 * \param[in] basY : plus petite ordonnée affichée
 * \return 0 si l'utilisateur a clique dans la grille
 * \return 1 si l'utilisateur à clique dans la zone de selection du joueur 1
 * \return 2 si l'utilisateur à clique dans la zone de selection du joueur 3
 * \return 3 si l'utilisateur clic dans la zone du bouton Pause
 * \return 4 si l'utilisateur clic dans la zone du bouton Aide
 * \return 5 si l'utilisateur clic dans la zone du bouton Quitter
	*/
int detecteCase(int *x, int *y, int zoom, unsigned int basX, unsigned int basY) {

    if (zoom < 1) {
        zoom = 1;
    }
    if (zoom >= TAILLEMAX) {
        zoom = TAILLEMAX - 1;
    }
    if (basX + zoom >= TAILLEMAX) {
        basX = (unsigned int) (TAILLEMAX - 1 - zoom);
    }
    if (basY + zoom >= TAILLEMAX) {
        basY = (unsigned int) (TAILLEMAX - 1 - zoom);
    }
    float largeur = largeurFenetre();
    float hauteur = hauteurFenetre();
    //Définit l'écart entre le centre de la fenêtre et le bord du plateau
    float ecart = (float) (((largeur <= hauteur) * largeur
                            + (largeur > hauteur) * hauteur) / 2.5);
    float taille =
            (largeurFenetre() >=
             hauteurFenetre()) * largeurFenetre() / 6 + (hauteurFenetre() >
                                                         largeurFenetre()) *
                                                        hauteurFenetre() / 6;
    int abs = abscisseSouris();
    int ord = ordonneeSouris();
    if (x != NULL && y != NULL) {
        //on regarde si l'utilisateur a cliqué dans la grille
        if (abs > (largeur / 2 - ecart) && abs < (largeur / 2 + ecart)
            && ord < (hauteur / 2 + ecart) && ord > (hauteur / 2 - ecart)) {
            float taille_case = 2 * ecart / zoom;
            *x = (int) (((abs + ecart - largeur / 2) / taille_case) + basX);
            *y = (int) (((ord + ecart - hauteur / 2) / taille_case) + basY);
            return 0;
        }
        *x = -1;
        *y = -1;
    }
    int x_min = (int) (taille / 10);
    int x_max = (int) (taille * 9 / 10);
    int y_max = hauteurFenetre() * 2 / 3;
    int y_min = (int) (y_max - taille * 8 / 10);

    if (estDansRectangle(abs, ord, x_min, y_min, x_max, y_max)) {

        return 1;
    }
    if (estDansRectangle(abs, ord, largeurFenetre() - x_min, y_min, largeurFenetre() - x_max,
                         y_max)) {
        return 2;
    }
    if (estDansRectangle(abs, ord, (int) (largeurFenetre() - 2.6f * taille), 0,
                         (int) (largeurFenetre() - 2.1f * taille),
                         (int) (2 * taille / 8))) {
        return 3;
    }
    if (estDansRectangle(abs, ord, (int) (largeurFenetre() - 2.1f * taille), 0,
                         (int) (largeurFenetre() - 1.65f * taille), (int) (2 * taille / 8))) {
        return 4;
    }
    if (estDansRectangle(abs, ord, (int) (largeurFenetre() - 1.65f * taille), 0, (int) (largeurFenetre() - taille),
                         (int) (2 * taille / 8))) {
        return 5;
    }
    return 0;
}

/*!
 * \brief change le zoom de la grille
 * \param [out] x_z : nouveau x minimum du zoom
 * \param [out] y_z : nouveau y minimum du zoom
 * \param [out] zoom : nouveau zoom
 * \param [in] up : true si c'est un zoom, false si c'est un dezoom
	*/
void changeZoom(unsigned int *x_z, unsigned int *y_z, unsigned int *zoom,
                bool up) {
    int x_c, y_c;
    int b = up ? -1 : 1;
    if ((*zoom > 1 || !up) && (*zoom < TAILLEMAX || up)) {
        if (detecteCase(&x_c, &y_c, *zoom, *x_z, *y_z) == 1) {
            if (up) {
                y_c = (y_c > (int) (*y_z + (*zoom) / 2)) ? (*y_z) + 2 : (*y_z);
                x_c = (x_c > (int) (*x_z + (*zoom) / 2)) ? (*x_z) + 2 : (*x_z);
            } else {
                y_c =
                        (y_c >
                         (int) (*y_z + (*zoom) / 2)) ? (*y_z) -
                                                       2 : (*y_z);
                x_c =
                        (x_c >
                         (int) (*x_z + (*zoom) / 2)) ? (*x_z) -
                                                       2 : (*x_z);

            }
            *zoom += b;
            *x_z = (unsigned int) x_c;
            *y_z = (unsigned int) y_c;
        }
    }
}

/*!
 * \brief affiche la durée de la partie depuis le debut de la partie
 * \param taille : taille des interfaces à afficher
	*/
void afficheDuree(int taille) {
    char chaine[20];
    int dure = gestionDuree(1);
    int H = dure / 3600;
    int m = (dure - H * 3600) / 60;
    int s = (dure - H * 3600 - m * 60);
    sprintf(chaine, "%.2dh%.2dm%.2ds", H, m, s);
    epaisseurDeTrait(1);
    couleurCourante(240, 255, 255);
    epaisseurDeTrait(1);
    afficheChaine(chaine, taille / 10, 2 * largeurFenetre() / 3,
                  hauteurFenetre() - taille / 4);
}

/*!
 * \brief fonction permettant de savoir si le clic est dans un rectangle
 * \param[in] xClic : abscisse du clic
 * \param[in] yClic : ordonnée du clic
 * \param[in] xMin : abscisse minimum du rectangle
 * \param[in] yMin : ordonnée minimum du rectangle
 * \param[in] xMax : abscisse maximum du rectangle
 * \param[in] yMax : ordonnee maximum du rectangle
 * \return true si le clic est dans le rectangle
 * \return false si le clic n'est pas dans le rectangle
 */
bool estDansRectangle(int xClic, int yClic, int xMin, int yMin, int xMax, int yMax) {
    int tmp;
    if (xMin > xMax) {
        tmp = xMin;
        xMin = xMax;
        xMax = tmp;
    }
    if (yMin > yMax) {
        tmp = yMin;
        yMin = yMax;
        yMax = tmp;
    }
    if (xClic > xMin && xClic < xMax && yClic > yMin && yClic < yMax) {
        return true;
    }
    return false;
}

/*!
 * \brief detecte la zone de clic du menu principale
 * \return 1 : jouer
 * \return 2 : option
 * \return 3 : aide
 * \return 4 : quitter
	*/
int detecteMenuPrincipal(void) {
    int abs = abscisseSouris();
    int ord = ordonneeSouris();
    int L = largeurFenetre();
    int H = hauteurFenetre();

    if (estDansRectangle(abs, ord, L * 2 / 5, H * 3 / 5, L * 3 / 5, H * 7 / 10)) {
        return 1;
    }
    if (estDansRectangle(abs, ord, L * 2 / 5, H * 9 / 20, L * 3 / 5, H * 11 / 20)) {
        return 2;
    }
    if (estDansRectangle(abs, ord, L * 2 / 5, H * 3 / 10, L * 3 / 5, H * 2 / 5)) {
        return 3;
    }
    if (estDansRectangle(abs, ord, L * 2 / 5, H * 3 / 20, L * 3 / 5, H / 4)) {
        return 4;
    }
    return 0;
}

/*!
 * \brief detecte la zone de clic du menu des options
 * \return 1 : mode de jeu
 * \return 2 : limite de temps
 * \return 3 : difficulté IA
 * \return 4 : changer de noms
 * \return 5 : retour
	*/
int detecteMenuOption(void) {
    int abs = abscisseSouris();
    int ord = ordonneeSouris();
    int L = largeurFenetre();
    int H = hauteurFenetre();

    if (estDansRectangle(abs, ord, L / 12, H * 3 / 5, L * 5 / 12, H * 7 / 10)) {
        return 1;
    }
    if (estDansRectangle(abs, ord, L / 12, H * 7 / 20, L * 5 / 12, H / 4)) {
        return 3;
    }
    if (estDansRectangle(abs, ord, L * 7 / 12, H * 3 / 5, L * 11 / 12, H * 7 / 10)) {
        return 2;
    }
    if (estDansRectangle(abs, ord, L * 7 / 12, H * 7 / 20, L * 11 / 12, H / 4)) {
        return 4;
    }
    if (estDansRectangle(abs, ord, 0, 0, L / 6, H / 10)) {
        return 5;
    }
    return 0;
}

/*!
 * \brief Affiche le score
 * \param [in] scoreJ1 : score du premier joueur
 * \param [in] scoreJ2 : score du deuxième joueur
	*/
void afficheScore(int scoreJ1, int scoreJ2) {

    couleurCourante(240, 255, 255);
    float taille =
            (largeurFenetre() >=
             hauteurFenetre()) * largeurFenetre() / 6 + (hauteurFenetre() >
                                                         largeurFenetre()) *
                                                        hauteurFenetre() / 6;
    char score[10];
    /**< variable de recuperation des scores*/

    afficheChaine("Score :", taille / 6, taille / 10, taille / 2);
    sprintf(score, "%d", scoreJ1);
    afficheChaine(score, taille / 6, taille / 10, taille / 4);

    afficheChaine("Score : ", taille / 6,
                  largeurFenetre() - taille * 9 / 10, taille / 2);
    sprintf(score, "%d", scoreJ2);
    afficheChaine(score, taille / 6, largeurFenetre() - taille * 9 / 10,
                  taille / 4);

}

/*!
 * \brief affiche le menu en jeu
 * \param[in] pause : true si le jeu est pause, false sinon
 */
void afficheMenuEnjeu(bool pause) {

    float taille =
            (largeurFenetre() >=
             hauteurFenetre()) * largeurFenetre() / 6 + (hauteurFenetre() >
                                                         largeurFenetre()) *
                                                        hauteurFenetre() / 6;
    //Affiche une indication si le jeu est en pause
    if(pause)
    {
        couleurCourante(200, 200, 200);
        rectangle(largeurFenetre()/2 - tailleChaine("PAUSE", 35), hauteurFenetre()/2 - 35, largeurFenetre()/2 + tailleChaine("PAUSE", 35), hauteurFenetre()/2 + 35);
        couleurCourante(63, 34, 4);
        epaisseurDeTrait(4);
        afficheChaine("PAUSE", 35, largeurFenetre()/2 - tailleChaine("PAUSE", 35)/2, hauteurFenetre()/2 - 17);
    }
    //affiche le rectangle noir de fond
    couleurCourante(0, 0, 0);
    rectangle(largeurFenetre() - 2.6f * taille, 0, largeurFenetre() - taille, 2 * taille / 8);
    //change la couleur du fond si une zone est survolé
    couleurCourante(63, 34, 4);
    switch (detecteCase(NULL, NULL, 0, 0, 0)) {
        case 3:
            rectangle(largeurFenetre() - 2.6f * taille, 0,
                      largeurFenetre() - 2.1f * taille, 2 * taille / 8);
            break;
        case 4:
            if (!pause) {
                rectangle(largeurFenetre() - 2.1f * taille, 0,
                          largeurFenetre() - 1.65f * taille, 2 * taille / 8);
            }
            break;
        case 5:
            rectangle(largeurFenetre() - 1.65f * taille, 0, largeurFenetre() - taille, 2 * taille / 8);
            break;
        default:
            break;
    }
    //affiche les rectangles autour des zones
    couleurCourante(240, 255, 255);
    rectangleVide(largeurFenetre() - 2.6f * taille, 0, largeurFenetre() - 2.1f * taille, 2 * taille / 8, 1);
    rectangleVide(largeurFenetre() - 2.1f * taille, 0, largeurFenetre() - 1.65f * taille, 2 * taille / 8, 1);
    rectangleVide(largeurFenetre() - 1.65f * taille, 0, largeurFenetre() - taille, 2 * taille / 8, 1);

    //affiche le texte
    afficheChaine("QUITTER", taille / 8, largeurFenetre() - 1.6f * taille, taille / 20);
    afficheChaine("INDICE", taille / 8, largeurFenetre() - 2.07f * taille, taille / 20);
    if (pause) {
        afficheChaine("CONTINUER", taille / 12, largeurFenetre() - 2.6f * taille, taille / 20);
    } else {
        afficheChaine("PAUSE", taille / 8, largeurFenetre() - 2.55f * taille, taille / 20);
    }

}

/*!
 * \brief trace un rectangle vide
 * \param[in] xCoin1 : abscisse du premier coin
 * \param[in] yCoin1 : ordonnée du premier coin
 * \param[in] xCoin2 : abscisse du second coin
 * \param[in] yCoin2 : ordonnée du second coin
 * \param[in] taille : epaisseur du trait
 */
void rectangleVide(float xCoin1, float yCoin1, float xCoin2, float yCoin2, float taille) {
    epaisseurDeTrait(taille);
    ligne(xCoin1, yCoin1, xCoin1, yCoin2);
    ligne(xCoin1, yCoin1, xCoin2, yCoin1);
    ligne(xCoin2, yCoin2, xCoin1, yCoin2);
    ligne(xCoin2, yCoin2, xCoin2, yCoin1);

}

/*!
 * \brief trace l'indice
 * \param[in] coupJoueur : structure contenant les informations concernant l'indice
 * \param[in] zoom : taille du zoom
 * \param[in] x : abcisse du zoom
 * \param[in] y : ordonnée du zoom
 */
void afficheIndice(coup coupJoueur, int zoom, int x, int y) {
    if (time(NULL) % 2 == 0) {
        return;
    }

    if (zoom < 1) {
        zoom = 1;
    }
    if (zoom >= TAILLEMAX) {
        zoom = TAILLEMAX - 1;
    }
    if (x + zoom >= TAILLEMAX) {
        x = TAILLEMAX - 1 - zoom;
    }
    if (y + zoom >= TAILLEMAX) {
        y = TAILLEMAX - 1 - zoom;
    }
    float largeur = largeurFenetre();
    float hauteur = hauteurFenetre();
    float ecart = (((largeur <= hauteur) * largeur
                    + (largeur > hauteur) * hauteur) / 2.5f);
    float taille_case = 2 * ecart / zoom;

    float minX, minY, maxX, maxY;
    if (coupJoueur.orientationPiece == BD) {
        minX = largeur / 2 - ecart + ((int) (coupJoueur.xCoup) - x) * taille_case;
        minY = hauteur / 2 - ecart + ((int) (coupJoueur.yCoup) - y - 1) * taille_case;
    } else if (coupJoueur.orientationPiece == BG) {
        minX = largeur / 2 - ecart + ((int) (coupJoueur.xCoup) - x - 1) * taille_case;
        minY = hauteur / 2 - ecart + ((int) (coupJoueur.yCoup) - y - 1) * taille_case;
    } else if (coupJoueur.orientationPiece == HG) {
        minX = largeur / 2 - ecart + ((int) (coupJoueur.xCoup) - x - 1) * taille_case;
        minY = hauteur / 2 - ecart + ((int) (coupJoueur.yCoup) - y) * taille_case;
    } else {
        minX = largeur / 2 - ecart + ((int) (coupJoueur.xCoup) - x) * taille_case;
        minY = hauteur / 2 - ecart + ((int) (coupJoueur.yCoup) - y) * taille_case;
    }
    maxX = minX + 2 * taille_case;
    maxY = minY + 2 * taille_case;
    affichePiece(coupJoueur.numeroPiece, coupJoueur.orientationPiece, (int) minX, (int) minY, (int) maxX, (int) maxY,
                 false);

}

/*!
 * \brief affiche l'écran pour changer le nom des joueur
 * \param[in] nomJ1 : nom du joueur 1
 * \param[in] nomJ2 : nom du joueur 2
 * \param[in] joueurActuel : joueur dont le nom est en train d'être modifié
 */
void afficheChangemntNom(char nomJ1[15], char nomJ2[15], int joueurActuel) {
    effaceFenetre(0, 0, 0);
    epaisseurDeTrait(1);
    int h = hauteurFenetre();
    int l = largeurFenetre();
    int taille1 = min(l, h) / 6;
    int taille2 = min(l, h) / 6;
    couleurCourante(240, 255, 255);
    rectangleVide(l / 10, h / 8, 9 * l / 10, 3 * h / 8, 10);
    rectangleVide(l / 10, 5 * h / 8, 9 * l / 10, 7 * h / 8, 10);
    char J1[15];
    char J2[15];
    char tiret[2] = "_";
    strcpy(J1, nomJ1);
    strcpy(J2, nomJ2);
    if (joueurActuel == 0 && strlen(nomJ1) < 14) {
        sprintf(J1, "%s%s", nomJ1, tiret);
    } else if (joueurActuel == 1 && strlen(nomJ2) < 14) {
        sprintf(J2, "%s%s", nomJ2, tiret);
    }
    while (tailleChaine(J1, taille1) > 8 * l / 10) {
        taille1 = taille1 - 5;
    }
    while (tailleChaine(J2, taille2) > 8 * l / 10) {
        taille2 = taille2 - 5;
    }
    afficheChaine(J1, taille1, l / 9, 5.5f * h / 8);
    afficheChaine(J2, taille2, l / 9, 1.5f * h / 8);

}

/*!
 * \brief change le nom du joueur actuel en fonction du dernier caractère clavier
 * \param[in/out] nomJ1 : nom du joueur 1
 * \param[in/out] nomJ2 : nom du joueur 2
 * \param[in] joueurActuel : joueur dont le nom est en train d'etre modifié
 * \return joueurActuel
 */
int changeNom(char nomJ1[15], char nomJ2[15], int joueurActuel) {

    char caractere = caractereClavier();
    char c[1] = {caractere};
    if (caractere > 31 && caractere < 127) {

        if (joueurActuel == 0 && strlen(nomJ1) < 14) {
            strcat(nomJ1, c);
        } else if (joueurActuel == 1 && strlen(nomJ2) < 14) {
            strcat(nomJ2, c);
        }
    }
    if (caractere == 8) {
        if (joueurActuel == 0) {
            nomJ1[strlen(nomJ1) - 1] = (char) 0;
        } else if (joueurActuel == 1) {
            nomJ2[strlen(nomJ2) - 1] = (char) 0;
        }
    } else if (caractere == 13) {
        joueurActuel = joueurActuel + 1;
    }
    return joueurActuel;
}

/*!
 * \brief affiche les temps restants des joueurs
 * \param[in] joueurActuel
 * le joueur dont ce n'est pas le tour voit son temps restant mis à zero
 */
void afficheTempRestant(int joueurActuel) {
    float taille = (largeurFenetre() >= hauteurFenetre()) * largeurFenetre() / 6 +
                   (hauteurFenetre() > largeurFenetre()) * hauteurFenetre() / 6;
    gestionDuree(((joueurActuel + 1) % 2) * 2 + 2);
    char tempJ1[5];
    char tempJ2[5];
    sprintf(tempJ1, "%d", gestionDuree(3));
    sprintf(tempJ2, "%d", gestionDuree(5));
    couleurCourante(240, 255, 255);
    afficheChaine(tempJ1, taille / 6, taille / 10, hauteurFenetre() * 8 / 10);
    afficheChaine(tempJ2, taille / 6, largeurFenetre() - 9 * taille / 10, hauteurFenetre() * 8 / 10);
}
