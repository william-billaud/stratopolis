/**
* \file main.c
* \brief fichier main
* \author Billaud William
* \author Hipault Theo
* \date 22/01/2107
*/

#include "affichage.h"
#include "ia.h"

/*!
 * \brief Fonction de gestion des evenements graphiques, a definir par l'utilisateur
 * \param evenement evement de la gfx à gérer
 */
void gestionEvenement(EvenementGfx evenement);

/// largeur par defaut d'une image correspondant a nos critères
#define LargeurFenetre 800
/// hauteur par defaut d'une image correspondant a nos critères
#define HauteurFenetre 600

/**
 * \brief fonction main
 * \param argc nombre d'argument
 * \param argv tableau contenant les argument
 * \return 0 si tout est bon
 */
int main(int argc, char **argv) {
    initialiseGfx(argc, argv);
    prepareFenetreGraphique("STRATOPOLIS", LargeurFenetre, HauteurFenetre);
    lanceBoucleEvenements();
    return 0;
}

/*!
 * \brief Fonction de gestion des evenements graphiques, a definir par l'utilisateur
 * \param evenement evement de la gfx à gérer
 */
void gestionEvenement(EvenementGfx evenement) {
    static bool pleinEcran = true;    // Pour savoir si on est en mode plein ecran ou pas
    static infoIa infoThread;
    static int debutHint;
    static enum {
        menu, classique, IA, victoire, tmpIA, hint, chgmtNom
    } mode, suivant;
    //position du zoom par defaut
    static unsigned int x_d = 80, y_d = 80;
    static unsigned int zoom_d = 20;
    //variable utilisé pour joué les coup
    int x, y;
    //variable utilisé pour stocker les coup du joueur
    static coup coupJoueur;
    //coup conseillé
    static coup coupHint;
    //variable utlilisé pour stocker l'orientation de la piece
    static orientation orientationPiece;
    //variable utilisé pour stocker le joueur actuelle
    static int joueurActuelle=1;
    //variable utilisé pour stocker le niveau de difficulté
    static int niveauDifficulte = 20;
    //nom des joueurs
    static char nomJ1[15] = "WilliambBILLAU";
    static char nomJ2[15] = "Theo";
    //permet de savoir si une pièce est selectionné
    static bool pieceSelectionne = false;
    int zoneDetecte;
    switch (evenement) {
        case Initialisation:
            modePleinEcran();
            mode = chgmtNom;
            suivant = classique;
            activeGestionDeplacementPassifSouris();
            demandeTemporisation(30);
            break;
        case Affichage:
            effaceFenetre(255, 255, 255);
            switch (mode) {
                case IA:
                    if (joueurActuelle == 1) {
                        infoThread.estFini = 0;
                        infoThread.niveauDifficulte = niveauDifficulte;
                        infoThread.joueur = joueurActuelle;
                        if (detacheThread_sur(threadIa, (void *) &infoThread)) {
                            mode = tmpIA;
                        }
                    }
                case classique:
                case hint:
                case tmpIA:
                    afficheInterface(nomJ1, nomJ2, joueurActuelle);
                    afficheGrille(zoom_d, x_d, y_d);
                    detecteCase(&x, &y, zoom_d, x_d, y_d);
                    if (pieceSelectionne) {
                        coupJoueur.orientationPiece = orientationPiece;
                        coupJoueur.yCoup = (unsigned int) y;
                        coupJoueur.xCoup = (unsigned int) x;
                        coupJoueur.numeroPiece = (unsigned char) ordreJoueurs[joueurActuelle][ordreJoueurs
                        [joueurActuelle][20]];
                        affichePredictif(coupJoueur, zoom_d);
                    }
                    //affiche l'indice
                    if (suivant == hint) {
                        //affiche l'indice
                        afficheIndice(coupHint, zoom_d, x_d, y_d);
                    }
                    break;
                case menu:
                    afficheMenu();
                    break;
                case victoire:
                    afficheChaine("PARTIE FINI ", 10, largeurFenetre() / 3, hauteurFenetre() / 2);
                    break;
                case chgmtNom:
                    afficheChangemntNom(nomJ1, nomJ2, joueurActuelle);
                    //TODO
                    break;


            }
            break;
        case Clavier:
            if (mode == chgmtNom && !toucheCtrlAppuyee()) {
                changeNom(nomJ1,nomJ2,joueurActuelle);
            } else {
                switch (caractereClavier()) {
                    case 'Q':
                    case 'q':
                        //ctrl +Q
                    case 17:
                        termineBoucleEvenements();
                        exit(0);
                    case 'F':
                    case 'f':
                        pleinEcran = !pleinEcran;    // Changement de mode plein ecran
                        if (pleinEcran)
                            modePleinEcran();
                        else
                            redimensionneFenetre(LargeurFenetre,
                                                 HauteurFenetre);
                        rafraichisFenetre();
                        break;

                    case 'R':
                    case 'r':
                        // On force un rafraichissement
                        rafraichisFenetre();
                        break;

                    case 'Z':
                    case 'z':
                        switch (mode) {

                            case classique:
                            case IA:
                            case hint:
                            case tmpIA:
                                trouveMeilleurZoom(&x_d, &y_d, &zoom_d);
                                break;
                            case victoire:
                            case menu:
                            case chgmtNom:
                                break;
                        }
                        rafraichisFenetre();
                        break;
                    default:
                        break;
                }
            }
            break;

        case ClavierSpecial:
            switch (mode) {
                case IA:
                case tmpIA:
                case hint:
                case classique:
                    switch (toucheClavier()) {
                        case ToucheFlecheDroite:
                        case ToucheFlecheBas:
                            orientationPiece = (orientationPiece + 1) % 4;
                            break;

                        case ToucheFlecheGauche:
                        case ToucheFlecheHaut:
                            if (orientationPiece == HD) {
                                orientationPiece = HG;
                            } else {
                                //(x+3)%4 =(x-1)%4 mais evite le problème des negatifs
                                orientationPiece = (orientationPiece + 3) % 4;
                            }
                            break;

                        default:
                            break;
                    }
                    break;
                case menu:
                    break;
                case chgmtNom:
                    // TODO
                    break;
                case victoire:
                    break;
            }
            rafraichisFenetre();
            break;

        case BoutonSouris:
            switch (mode) {
                case classique:
                case hint:
                case IA:
                case tmpIA:
                    switch (etatBoutonSouris()) {
                        case GaucheAppuye:
                            zoneDetecte = detecteCase(&x, &y, zoom_d, x_d, y_d);
                            if (mode == classique || (mode == IA && joueurActuelle == 0)) {
                                if (pieceSelectionne && zoneDetecte == 0) {
                                    coupJoueur.orientationPiece = orientationPiece;
                                    coupJoueur.yCoup = (unsigned int) y;
                                    coupJoueur.xCoup = (unsigned int) x;
                                    coupJoueur.numeroPiece = (unsigned char)
                                            ordreJoueurs[joueurActuelle][ordreJoueurs
                                            [joueurActuelle][20]];
                                    orientationPiece = HD;
                                    if (joueCoup(coupJoueur) == 1) {
                                        ordreJoueurs[joueurActuelle][20] += 1;
                                        joueurActuelle = (joueurActuelle + 1) % 2;
                                        if (ordreJoueurs[1][20] == 20
                                            && ordreJoueurs[0][20] == 20) {
                                            joueurActuelle = calculScore(0) > calculScore(1) ? 0 : 1;
                                            mode = victoire;
                                        }
                                    }
                                    pieceSelectionne = false;
                                    suivant = menu;
                                } else if (zoneDetecte == joueurActuelle + 1) {
                                    pieceSelectionne = !pieceSelectionne;
                                }
                            }
                            if (zoneDetecte == 3) {

                            } else if (zoneDetecte == 4) {
                                infoThread.estFini = 0;
                                infoThread.niveauDifficulte = 0;
                                infoThread.joueur = joueurActuelle;
                                if (detacheThread_sur(threadIa, (void *) &infoThread)) {
                                    suivant = mode;
                                    mode = hint;
                                }
                            } else if (zoneDetecte == 5) {
                                mode = menu;
                            }

                            break;
                        case ScrollUp:
                            if (toucheCtrlAppuyee()) {
                                changeZoom(&x_d, &y_d, &zoom_d, true);
                            } else if (pieceSelectionne) {
                                orientationPiece = (orientationPiece + 1) % 4;
                            }
                            break;
                        case ScrollDown:
                            if (toucheCtrlAppuyee()) {
                                changeZoom(&x_d, &y_d, &zoom_d, false);
                            } else if (pieceSelectionne) {
                                orientationPiece = (orientationPiece - 1) % 4;
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
                    break;
                case victoire:
                    switch (etatBoutonSouris()) {

                        case GaucheAppuye:
                        case DroiteAppuye:
                            mode = menu;
                            break;
                        case GaucheRelache:
                            break;
                        case DroiteRelache:
                            break;
                        case ScrollUp:
                            break;
                        case ScrollDown:
                            break;
                        case TmpScroll:
                            break;
                    }
                    break;
                case menu:
                    switch (detecteMenuPrincipal()) {
                        case 1:
                            initPartie(&joueurActuelle);
                            trouveMeilleurZoom(&x_d, &y_d, &zoom_d);
                            mode = suivant;
                            break;
                        case 2:
                            //option
                            break;
                        case 3:
                            //aide
                            break;
                        case 4:
                            termineBoucleEvenements();
                            exit(0);
                        default:
                            break;
                    }
                    break;
                case chgmtNom:
                    // TODO
                    break;
            }

            rafraichisFenetre();
            break;
        case Souris:
            switch (mode) {

                case menu:
                case chgmtNom:
                case classique:
                case IA:
                case victoire:
                case hint:
                case tmpIA:
                    rafraichisFenetre();
                    break;
            }
            break;
        case Inactivite:
            break;
        case Temporisation:
            if (mode == tmpIA) {
                if (infoThread.estFini != 0) {
                    if (infoThread.estFini == 1) {
                        if (joueCoup(infoThread.coupIA) == 1) {
                            ordreJoueurs[joueurActuelle][20] += 1;
                            joueurActuelle = (joueurActuelle + 1) % 2;
                        }
                    } else {
                        mode = menu;
                    }
                    trouveMeilleurZoom(&x_d, &y_d, &zoom_d);
                    mode = IA;
                    if (ordreJoueurs[1][20] == 20
                        && ordreJoueurs[0][20] == 20) {
                        joueurActuelle = calculScore(0) > calculScore(1) ? 0 : 1;
                        mode = victoire;
                    }
                }
            }
            if (mode == hint) {
                if (infoThread.estFini != 0) {
                    if (infoThread.estFini == 1) {
                        coupHint = infoThread.coupIA;
                        mode = suivant;
                        suivant = hint;
                        debutHint = (int) time(NULL);
                    } else {
                        mode = menu;
                    }
                }
            }
            if (suivant == hint) {
                //l'indice ne s'affiche que 5 secondes
                if ((time(NULL) - 5) > debutHint) {
                    suivant = menu;
                }
            }
            rafraichisFenetre();
            break;
        case Redimensionnement:
            rafraichisFenetre();
            break;
    }
}
