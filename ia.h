/*!
   \file ia.h
   \brief fichier contenant les prototypes fonctions necessaires au fonctionnement de l'ia et les structures de données necessaires
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
 * \brief structure utilisée pour la recherche d'un coup par l'ia sur un thread parallèle
 */
typedef struct infoIa{
    int estFini /*!< entier pour connaitre l'etat de la recherche, 0 : en cour; 1 : succès; 2 : echec*/;
    int joueur /*!< joueur dont le coup doit être trouvé*/;
    int niveauDifficulte/*!< niveau de difficulté ( nombre de recusion)*/;
    coup coupIA /*!< coup d'ia retourné par la fonction  */;
}infoIa;

/*!
 * \brief cherche un coup pour l'ia
 * \param[in] joueur : joueur joué par l'ia
 * \param[in] niveauDifficulte : niveau de difficulté de l'ia
 * \param[in]etat entier permettant d'arreter la recherche de l'IA si necessaire
 * \return un coup proposé par l'ia
  */
coup coupIA(int joueur, int niveauDifficulte,int *etat);

/*!
 * \brief algorithme min max
 * \param joueurActuel : joueur qui doit jouer
 * \param joueurIA : joueur remplacé par l'IA
 * \param ProfondeurActuelle : nombre de recursions
 * \param ProfondeurMaximum : nombre de recursions maximum
 * \param alpha : valeur du Alpha
 * \param beta : valeur du beta
 * \param tourActuelle : numero du tour actuel (= nombre de pièces posées depuis le début de la partie
 * \param[in]etat entier permettant d'arreter la recherche de l'IA si necessaire
 * \return score de la situation
  */
int minMax(int joueurActuel, int joueurIA, int ProfondeurActuelle,
           int ProfondeurMaximum, int alpha, int beta, int tourActuelle,int *etat);

/*!
* \brief fonction à lancer dans un thread parallèle pour trouver le coup de l'ia
* \param args : pointeur vers une structure de type (infoIa)
* \return
*
* la fonction modifie l'etat de l'entier estFinie de la structure pointée en entrée, elle prend le statut 1 si tout est OK et 2 sinon,
* l'état de base est le 0
* elle modifie la variable coupIA de la structure par le meilleur coup trouvé
*/
void *threadIa(void *args);
#endif PROJET_IA_H
