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
    //variable utilisé pour joué les coup
    int x, y;
    //variable utilisé pour stocker les coup du joueur
    static coup coupJoueur;
    //variable utlilisé pour stocker l'orientation de la piece
    static orientation orientationPiece;
    //variable utilisé pour stocker le joueur actuelle
    static int joueurActuelle;
    //variable utilisé pour stocker le niveau de difficulté
    static int niveauDifficulte = 1;
    //nom des joueurs
    static char nomJ1[15]="William";
    static char nomJ2[15]="Theo";
    //permet de savoir si une pièce est selectionné
    static bool pieceSelectionne=false;
    switch (evenement) {
        case Initialisation:
            modePleinEcran();
            initPartie(&joueurActuelle);
            trouveMeilleurZoom(&x_d, &y_d, &zoom_d);
            mode = IA;
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
                    break;
                case victoire:
                    afficheChaine("PARTIE FINI ",10,largeurFenetre()/3,hauteurFenetre()/2);
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
                                orientationPiece=(orientationPiece+1)%4;
                            break;

                        case ToucheFlecheGauche:
                        case ToucheFlecheHaut:
                            if (orientationPiece == HD) {
                                orientationPiece = HG;
                            } else {
                                //(x+3)%4 =(x-1)%4 mais evite le problème des negatifs
                                orientationPiece=(orientationPiece+3)%4;
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
                                           joueurActuelle= calculScore(0) > calculScore(1)?0:1;
                                                mode =victoire;
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
                            } else if(pieceSelectionne){
                                orientationPiece=(orientationPiece+1)%4;
                            }
                            break;
                        case ScrollDown:
                            if (toucheCtrlAppuyee()) {
                                changeZoom(&x_d, &y_d, &zoom_d, false);
                            } else if(pieceSelectionne){
                                orientationPiece=(orientationPiece-1)%4;
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
                    switch (etatBoutonSouris())
                    {

                        case GaucheAppuye:
                        case DroiteAppuye:
                            mode=menu;
                            break;
                        case GaucheRelache:break;
                        case DroiteRelache:break;
                        case ScrollUp:break;
                        case ScrollDown:break;
                        case TmpScroll:break;
                    }
                    break;
                case menu:
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
                                joueurActuelle= calculScore(0) > calculScore(1)?0:1;
                                mode =victoire;
                            }
                        }
                    } else {
                        mode = menu;
                    }
                    trouveMeilleurZoom(&x_d, &y_d, &zoom_d);
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
