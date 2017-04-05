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
/*!
 * \brief structure utilisé pour la recherche d'un coup par l'ia sur un thread parallèle
 */
typedef struct infoIa{
    int estFini /*!< entier pour connaitre l'etat de la recherche, 0 : en cour; 1 : succès; 2 : echec*/;
    int joueur /*!< joueur dont le coup doit etres trouve*/;
    int niveauDifficulte/*!< niveau de difficulte ( nombre de recusion)*/;
    coup coupIA /*!< coup d'ia retourne par la fonction  */;
}infoIa;

/*!
\brief cherche un coup pour l'ia
\param[in] joueur : joueur jouer par l'ia
\param[in] niveauDifficulte : niveau de difficulté de l'ia
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

/*!
* \brief fonction à lancer dans un thread parrallèle pour trouver le coup de l'ia
* \param args pointeur vers une structure de type (infoIa)
* \return
*
* la fonction modifie l'etat de l'entire estFinie de la structure pointe en entrée, elle prend la statut 1 si tout est OK et 2 sinon, l'etat de base est le 0
* elle modifie la variable coupIA de la structure pas le meilleur coup trouvé
*/
void *threadIa(void *args);
#endif //PROJET_IA_H
