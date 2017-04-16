/*!
   \file ia.c
   \brief fichier contenant les fonctions necessaires au fonctionnement de l'ia
   \author Billaud William
   \author Hipault Theo
   \date 04/04/2017
*/

#include "ia.h"

/*!
 * \brief cherche un coup pour l'ia
 * \param[in] joueur : joueur joué par l'ia
 * \param[in] niveauDifficulte : niveau de difficulté de l'ia
 * \param[in] etat entier permettant d'arreter la recherche de l'IA si necessaire
 * \return un coup proposé par l'ia
 */
coup coupIA(int joueur, int niveauDifficulte,int *etat) {
    coup cp;
    //variable pour stocker le meilleur coup
    coup meilleurCp;
    int max = -32000;
    int res;
    //les differents index
    unsigned int i;
    unsigned int j;
    int i_o;
    //variables necessaires pour reduire le nombre de possibilités à tester
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
    //on reduit le champ des possibiltés
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
                if (joueCoup(cp)==1) {
                    res =
                            minMax((joueur + 1) % 2, joueur, 0,
                                   profondeurMax, -32767, 32767,
                                   nbPieceJoue + 1,etat);
                    if(dejoueCoup(cp)==-1)
                    {
                        puts("error dejoue coup");
                    }
                    if (res > max) {
                        max = res;
                        meilleurCp = cp;
                    }
                }
                //procedure d'arret brutal
                if(*etat==3)
                {
                    return meilleurCp;
                }
            }
        }
    }
    return meilleurCp;
}

/*!
 * \brief algorithme min max
 * \param[in] joueurActuel : joueur qui doit jouer
 * \param[in] joueurIA : joueur remplacé par l'IA
 * \param[in] ProfondeurActuelle : nombre de recursions
 * \param[in] ProfondeurMaximum : nombre de recursions maximum
 * \param[in] alpha : valeur du Alpha
 * \param[in] beta : valeur du beta
 * \param[in] tourActuelle : numero du tour actuel (= nombre de pièces posées depuis le début de la partie
 * \param[in] etat entier permettant d'arreter la recherche de l'IA si necessaire
 * \return score de la situation
 */
int minMax(int joueurActuel, int joueurIA, int ProfondeurActuelle,
           int ProfondeurMaximum, int alpha, int beta, int tourActuelle,int *etat) {
    //si P est une feuille alors
    //cad : plus de pièces à jouer ou profondeur atteinte.
    int val;
    //tableau simplifiant le parcours des rotations possibles
    orientation or[4] = {HD, HG, BD, BG};
    unsigned int l;
    unsigned int h;
    unsigned int i;
    unsigned int j;
    int i_o;
    unsigned int zoom;
    coup cp;
    if (ProfondeurActuelle == ProfondeurMaximum || tourActuelle == 40 || *etat==3) {
        return calculScore(joueurIA) - calculScore((joueurIA + 1) % 2);
    } else {
        //on reduit le champ des possibiltés
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
                        if (joueCoup(cp)==1) {
                            //Val = Min(Val, ALPHABETA(Pi, alpha, beta))
                            val =
                                    min(val,
                                        minMax((joueurActuel + 1) % 2, joueurIA, ProfondeurActuelle + 1,
                                               ProfondeurMaximum, alpha, beta, tourActuelle + 1,etat));
                            if(dejoueCoup(cp)==-1)
                            {
                                puts("error dejoue coup");
                            }
                            //si alpha ≥ Val alors  /* coupure alpha */
                            if (alpha >= val) {
                                //retourner Val
                                return val;
                            }
                            //finsi
                            //beta = Min(beta, Val)
                            beta = min(beta, val);
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
                                             ProfondeurMaximum, alpha, beta, tourActuelle + 1,etat));

                            if(dejoueCoup(cp)==-1)
                            {
                                puts("error dejoue coup");
                            }
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
    }            //finsi
}                //fin

/*!
* \brief fonction à lancer dans un thread parallèle pour trouver le coup de l'ia
* \param[in,out] args : pointeur vers une structure de type (infoIa)
* \return
*
* la fonction modifie l'etat de l'entier estFinie de la structure pointée en entrée, elle prend le statut 1 si tout est OK et 2 sinon,
* l'état de base est le 0
* elle modifie la variable coupIA de la structure par le meilleur coup trouvé
*/
void *threadIa(void *args)
{
    infoIa* i= (infoIa*) args;
    i->coupIA=coupIA(i->joueur, i->niveauDifficulte, &(i->estFini));
    if(i->coupIA.numeroPiece==42)
    {
        i->estFini=2;
    } else{
        i->estFini=1;
    }
    pthread_exit(NULL);
}
