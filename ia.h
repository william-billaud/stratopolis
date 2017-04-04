/*!
   \file ia.h
   \brief fichier contenant les prototypes fonctions necessaires au fonctionnement de l'ia et le structure de donnée necessaires
   \author Billaud William
   \author Hipault Theo
   \date 04/04/2017

*/

#ifndef PROJET_IA_H
#define PROJET_IA_H
#include "moteur.h"
#include <pthread.h>
#include "lib/ThreadLib.h"

typedef struct infoIa{
    int estFini;
    int joueur;
    int niveauDifficulte;
    coup coupIA;
}infoIa;
/*!
\brief cherche un coup pour l'ia
\param[in] joueur : joueur jouer par l'ia
\param[in] niveauDifficulte : niveau de difficulté de l'ia
\param[in] nbPieceJoue : nombre de pièces deja
\return un coup proposé par l'ia
*/
coup coupIA(int joueur, int niveauDifficulte);


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
           int ProfondeurMaximum, int alpha, int beta, int tourActuelle);

void *threadIa(void *args);
#endif //PROJET_IA_H
