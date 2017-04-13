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
        menu, classique, IA, victoire, tmpIA, hint, chgmtNom, option
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
    static int joueurActuelle = 0;
    //variable utilisé pour stocker le niveau de difficulté
    static int niveauDifficulte = 1;
    //nom des joueurs
    static char nomJ1[15] = "Joueur 1";
    static char nomJ2[15] = "Joueur 2";
    //permet de savoir si une pièce est selectionné
    static bool pieceSelectionne = false;
    int zoneDetecte;
    //inidique si la limite de temp est activé ou non
    static bool limiteTemp = false;
    //durée de la limite de temp
    static unsigned int dureeLimite = 0;
    //si le mode pause est activée
    static bool pause=false;
    switch (evenement) {
        case Initialisation:
            modePleinEcran();
            mode = menu;
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
                    afficheMenuEnjeu(pause);
                    detecteCase(&x, &y, zoom_d, x_d, y_d);
                    if (pieceSelectionne && !pause) {
                        coupJoueur.orientationPiece = orientationPiece;
                        coupJoueur.yCoup = (unsigned int) y;
                        coupJoueur.xCoup = (unsigned int) x;
                        coupJoueur.numeroPiece = (unsigned char) ordreJoueurs[joueurActuelle][ordreJoueurs
                        [joueurActuelle][20]];
                        affichePredictif(coupJoueur, zoom_d);
                    }
                    //affiche l'indice
                    if (suivant == hint && !pause) {
                        //affiche l'indice
                        afficheIndice(coupHint, zoom_d, x_d, y_d);
                    }
                    if (limiteTemp && classique) {
                        afficheTempRestant(joueurActuelle);
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
                case option:
                    afficheOption(limiteTemp, dureeLimite, niveauDifficulte, suivant);
                    break;


            }
            break;
        case Clavier:
            if (mode == chgmtNom && !toucheCtrlAppuyee()) {
                joueurActuelle = changeNom(nomJ1, nomJ2, joueurActuelle);
                if (joueurActuelle > 1) {
                    joueurActuelle = 1;
                    mode = option;
                }
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
                            case option:
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
                    if(!pause) {
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
                    }
                    break;
                case menu:
                    break;
                case chgmtNom:
                    // TODO
                    break;
                case victoire:
                    break;
                case option:
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
                            if (mode == classique || (mode == IA && joueurActuelle == 0) ) {
                                if (pieceSelectionne && zoneDetecte == 0 && !pause) {
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
                                            suivant = mode;
                                            gestionDuree(7);
                                            pause=false;
                                            mode = victoire;

                                        }
                                        gestionDuree(joueurActuelle * 2 + 2);
                                    }
                                    pieceSelectionne = false;
                                } else if (zoneDetecte == joueurActuelle + 1 && !pause) {
                                    pieceSelectionne = !pieceSelectionne;
                                }
                            }
                            if (zoneDetecte == 3) {
                                if(pause)
                                {
                                    gestionDuree(7);
                                } else{
                                    gestionDuree(6);
                                }
                                pause=!pause;

                            } else if (zoneDetecte == 4 && !pause) {
                                infoThread.estFini = 0;
                                infoThread.niveauDifficulte = 0;
                                infoThread.joueur = joueurActuelle;
                                if (detacheThread_sur(threadIa, (void *) &infoThread)) {
                                    suivant = mode;
                                    mode = hint;
                                }
                            } else if (zoneDetecte == 5) {
                                if(suivant==IA  || suivant==tmpIA)
                                {
                                    suivant=IA;
                                }else
                                {
                                    suivant=classique;
                                }
                                gestionDuree(7);
                                pause=false;
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
                            mode = option;
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
                case option:
                    if (etatBoutonSouris() == GaucheAppuye) {
                        switch (detecteMenuOption()) {
                            case 1:
                                if (suivant == classique) {
                                    suivant = IA;
                                } else {
                                    suivant = classique;
                                }
                                break;
                            case 2:
                                if (suivant == classique) {
                                    if (!limiteTemp) {
                                        limiteTemp = true;
                                        dureeLimite = 30;
                                    } else if (dureeLimite == 30) {
                                        dureeLimite = 120;
                                    } else if (dureeLimite == 120) {
                                        dureeLimite = 300;
                                    } else {
                                        limiteTemp = false;
                                    }
                                }
                                rafraichisFenetre();
                                break;
                            case 3:
                                if (suivant == IA) {
                                    niveauDifficulte = 1 + (niveauDifficulte) % 5;
                                }
                                break;
                            case 4:
                                joueurActuelle = 0;
                                mode = chgmtNom;
                                break;
                            case 5:
                                mode = menu;
                                break;
                            default:
                                break;
                        }
                    }
                    break;
            }
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
                case option:
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
                        suivant = mode;
                        mode = victoire;
                        pause=false;
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
            if (mode == classique && limiteTemp) {
                if (gestionDuree(joueurActuelle * 2 + 3) >= (int) dureeLimite) {
                    coupJoueur = coupAleatoire(joueurActuelle);
                    if (joueCoup(coupJoueur) == 1) {
                        ordreJoueurs[joueurActuelle][20] += 1;
                        joueurActuelle = (joueurActuelle + 1) % 2;
                        if (ordreJoueurs[1][20] == 20
                            && ordreJoueurs[0][20] == 20) {
                            joueurActuelle = calculScore(0) > calculScore(1) ? 0 : 1;
                            suivant = mode;
                            mode = victoire;
                            gestionDuree(7);
                            pause=false;

                        }
                        gestionDuree(joueurActuelle * 2 + 2);
                    }
                }
            }
            rafraichisFenetre();
            break;
        case Redimensionnement:
            rafraichisFenetre();
            break;
    }
}
