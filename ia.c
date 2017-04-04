/*!
   \file ia.c
   \brief fichier contenant les fonctions necessaires au fonctionnement de l'ia
   \author Billaud William
   \author Hipault Theo
   \date 04/04/2017

*/

#include "ia.h"

/*!
\brief cherche un coup pour l'ia
\param[in] joueur : joueur jouer par l'ia
\param[in] niveauDifficulte : niveau de difficulté de l'ia
\param[in] nbPieceJoue : nombre de pièces deja
\return un coup proposé par l'ia
*/
coup coupIA(int joueur, int niveauDifficulte) {
    coup cp;
    //variable pour stocker le meilleur coup
    coup meilleurCp;
    int max = -32000;
    int res;
    //les differents indexw
    unsigned int i;
    unsigned int j;
    int i_o;
    //variables necessaire pour reduire le nombre de possibilité à tester
    unsigned int zoom;
    unsigned int l;
    unsigned int h;
    int profondeurMax = niveauDifficulte;
    int nbPieceJoue = ordreJoueurs[0][20] + ordreJoueurs[1][20];
    orientation or[4] = {HD, HG, BD, BG};
    meilleurCp.numeroPiece = 42;
    meilleurCp.yCoup = 0;
    meilleurCp.xCoup = 0;
    meilleurCp.orientationPiece = HD;
    //on reduit le champ des possibilté
    if (trouveMeilleurZoom(&l, &h, &zoom) == -1) {
        return meilleurCp;
    }
    //le numero de la pièce pour ce coup
    cp.numeroPiece = (unsigned int) ordreJoueurs[joueur][nbPieceJoue / 2];
    for (i = l; i < l + zoom; ++i) {
        for (j = h; j < h + zoom; ++j) {
            for (i_o = 0; i_o < 4; ++i_o) {
                cp.orientationPiece = or[i_o];
                cp.xCoup = i;
                cp.yCoup = j;
                if (estValideCoup(cp)) {
                    joueCoup(cp);
                    res =
                            minMax((joueur + 1) % 2, joueur, 0,
                                   profondeurMax, 32767, 0,
                                   nbPieceJoue + 1);
                    dejoueCoup(cp);
                    if (res > max) {
                        max = res;
                        meilleurCp = cp;
                    }
                }
            }
        }
    }
    return meilleurCp;
}

/*!
 * \brief algorithme min max
 * \param joueurActuel joueur qui doit jouer
 * \param joueurIA joueur remplacé par l'IA
 * \param ProfondeurActuelle nombre de recursion
 * \param ProfondeurMaximum nom de recursion maximum
 * \param alpha valeur du Alpha
 * \param beta valeur du beta
 * \param tourActuelle numero du tour actuelle (= nombre de pièces posées depuis le début de la partie
 * \return score de la situation
 */
int minMax(int joueurActuel, int joueurIA, int ProfondeurActuelle,
           int ProfondeurMaximum, int alpha, int beta, int tourActuelle) {
    //si P est une feuille alors
    //cad : plus de pièce à jouer ou profondeur atteinte.
    int val;
    static int compteur = 0;
    compteur += 1;
    //tableau simplifiant le parcours des rotations possibles
    orientation or[4] = {HD, HG, BD, BG};
    unsigned int l;
    unsigned int h;
    unsigned int i;
    unsigned int j;
    int i_o;
    unsigned int zoom;
    coup cp;
    if (ProfondeurActuelle == ProfondeurMaximum || tourActuelle == 40) {
        //retourner la valeur de P
        printf("Nb recursion environ : %d \n", compteur);
        return calculScore(joueurIA) - calculScore((joueurIA + 1) % 2);
    } else {
        //on reduit le champ des possibilté
        trouveMeilleurZoom(&l, &h, &zoom);
        //le numero de la pièce pour ce coup
        cp.numeroPiece =
                (unsigned int) ordreJoueurs[joueurActuel][tourActuelle / 2];
        //si P est un nœud Min alors
        if (joueurActuel != joueurIA) {
            //Val = infini
            val = 32767;
            for (i = l; i < l + zoom; ++i) {
                for (j = h; j < h + zoom; ++j) {
                    for (i_o = 0; i_o < 4; ++i_o) {
                        cp.orientationPiece = or[i_o];
                        cp.xCoup = i;
                        cp.yCoup = j;
                        if (estValideCoup(cp)) {
                            joueCoup(cp);
                            //Val = Min(Val, ALPHABETA(Pi, alpha, beta))
                            val =
                                    min(val,
                                        minMax((joueurActuel + 1) % 2, joueurIA, ProfondeurActuelle + 1,
                                               ProfondeurMaximum, alpha, beta, tourActuelle + 1));
                            dejoueCoup(cp);
                            //si alpha ≥ Val alors  /* coupure alpha */
                            if (alpha >= val) {
                                //retourner Val
                                return val;
                            }
                            // finsi
                            //beta = Min(beta, Val)
                            beta = min(beta, val);
                            dejoueCoup(cp);
                        }
                    }
                }
            }
            //finpour
        } else {
            //sinon
            //Val = -infini
            val = -32000;
            //pour tout enfant Pi de P faire
            for (i = l; i < l + zoom; ++i) {
                for (j = h; j < h + zoom; ++j) {
                    for (i_o = 0; i_o < 4; ++i_o) {
                        cp.orientationPiece = or[i_o];
                        cp.xCoup = i;
                        cp.yCoup = j;
                        if (estValideCoup(cp)) {
                            joueCoup(cp);
                            //Val = Max(Val, ALPHABETA(Pi, alpha, beta))
                            val = max(val,
                                      minMax((joueurActuel + 1) % 2, joueurIA, ProfondeurActuelle + 1,
                                             ProfondeurMaximum, alpha, beta, tourActuelle + 1));
                            dejoueCoup(cp);
                            //Val ≥ beta alors /* coupure beta */
                            if (beta <= val) {
                                //retourner Val
                                return val;
                            }
                            // finsi
                            //alpha = Max(alpha, Val)
                            alpha = max(alpha, val);
                        }
                    }
                }
            }    //finpour
        }        //finsi
        return val;
    }            // finsi
}                //fin

/*!
* \brief fonction à lancer dans un thread parrallèle pour trouver le coup de l'ia
* \param args pointeur vers une structure de type (infoIa)
* \return
*
* la fonction modifie l'etat de l'entire estFinie de la structure pointe en entrée, elle prend la statut 1 si tout est OK et 2 sinon, l'etat de base est le 0
* elle modifie la variable coupIA de la structure pas le meilleur coup trouvé
*/
void *threadIa(void *args)
{
    infoIa* i= (infoIa*) args;
    i->coupIA=coupIA(i->joueur,i->niveauDifficulte);
    if(i->coupIA.numeroPiece==42)
    {
        i->estFini=2;
    } else{
        i->estFini=1;
    }
    pthread_exit(NULL);
}