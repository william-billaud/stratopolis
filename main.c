/**
* \file main.c
* \brief fichier main
* \author Billaud William
* \author Hipault Theo
* \date 22/01/2107
*/

#include "affichage.h"
#include "ia.h"

#define LargeurFenetre 800
/// hauteur par defaut d'une image correspondant a nos critères
#define HauteurFenetre 600

/*!
 * \brief
 * \param evenement
 */
void gestionEvenement(EvenementGfx evenement);

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
 * \brief
 * \param evenement
 */
void gestionEvenement(EvenementGfx evenement) {
    static bool pleinEcran = true;    // Pour savoir si on est en mode plein ecran ou pas
    static infoIa infoThread;
    static enum {
        menu, classique, IA, victoire, tmpIA
    } mode;
    //position du zoom par defaut
    static unsigned int x_d = 80, y_d = 80;
    static unsigned int zoom_d = 20;
    int x, y;
    static coup coupJoueur;
    static orientation orientationPiece;
    static int joueurActuelle;
    static int niveauDifficulte = 1;
    static char nomJ1[15]="William";
    static char nomJ2[15]="Theo";
    static bool pieceSelectionne=false;
    switch (evenement) {
        case Initialisation:
            modePleinEcran();
            initPartie(&joueurActuelle);
            joueurActuelle = 0;
            trouveMeilleurZoom(&x_d, &y_d, &zoom_d);
            mode = classique;
            activeGestionDeplacementPassifSouris();
            demandeTemporisation(1000);
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
                case tmpIA:
                    afficheInterface(nomJ1,nomJ2,joueurActuelle);
                    afficheGrille(zoom_d, x_d, y_d);
                    detecteCase(&x, &y, zoom_d, x_d, y_d);
                    if(pieceSelectionne) {
                        coupJoueur.orientationPiece = orientationPiece;
                        coupJoueur.yCoup = (unsigned int) y;
                        coupJoueur.xCoup = (unsigned int) x;
                        coupJoueur.numeroPiece = (unsigned char) ordreJoueurs[joueurActuelle][ordreJoueurs
                        [joueurActuelle][20]];
                        affichePredictif(coupJoueur, zoom_d);
                    }
                    break;
                case menu:
                case victoire:
                    break;

            }

            break;

        case Clavier:
            switch (caractereClavier()) {
                case 'Q':
                case 'q':
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
                        case tmpIA:
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
            switch (mode) {
                case IA:
                case tmpIA:
                case classique:
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
                    break;
                case menu:
                    break;
                case victoire:
                    break;
            }
            rafraichisFenetre();
            break;

        case BoutonSouris:
            switch (mode) {
                case classique:
                case IA:
                    switch (etatBoutonSouris()) {
                        case GaucheAppuye:
                            if (mode == classique || (mode == IA && joueurActuelle == 0)) {

                                if(pieceSelectionne && detecteCase(&x, &y, zoom_d, x_d, y_d)==0) {
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
                                            if (calculScore(0) > calculScore(1)) {
                                                puts("joueur vert à gagné");
                                            } else {
                                                puts("joueur rouge à gagné");
                                            }
                                            initPartie(&joueurActuelle);
                                        }
                                    }
                                    pieceSelectionne = false;
                                }else if(detecteCase(&x, &y, zoom_d, x_d, y_d)==joueurActuelle+1)
                                {
                                    pieceSelectionne=true;
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
                    break;
                case menu:
                    break;
                case victoire:
                    break;
                case tmpIA:
                    break;
            }

            rafraichisFenetre();
            break;

        case Souris:

            rafraichisFenetre();
            break;

        case Inactivite:
            rafraichisFenetre();
            break;
        case Temporisation:
            if (mode == tmpIA) {
                if (infoThread.estFini != 0) {
                    if (infoThread.estFini == 1) {
                        if (joueCoup(infoThread.coupIA) == 1) {
                            ordreJoueurs[joueurActuelle][20] += 1;
                            joueurActuelle = (joueurActuelle + 1) % 2;
                            if (ordreJoueurs[1][20] == 20
                                && ordreJoueurs[0][20] == 20) {
                                if (calculScore(0) > calculScore(1)) {
                                    mode = victoire;
                                } else {
                                    mode = victoire;
                                }
                                initPartie(&joueurActuelle);
                            }
                        }
                    } else {
                        mode = menu;
                    }
                    mode = IA;
                }
            }
            rafraichisFenetre();
            break;
        case Redimensionnement:
            rafraichisFenetre();
            break;
    }

}
