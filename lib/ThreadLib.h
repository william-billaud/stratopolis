/* Veuillez reporter tout commentaire a ghislain.oudinet@isen.fr */
/*!
   \file ThreadLib.h
   \brief fichier utile pour le lancement de thread en parallele
   \author Ghislain Oudinet
   \date 26/04/07.

   Sous Linux : linker avec -lpthread
*/

/*
 *  ThreadLib.h
 *  isentlib
 *
 *  Created by Ghislain Oudinet on 26/04/07.
 *
 */

// Sous Linux : linker avec -lpthread

#ifndef THREADLIB_H
#define THREADLIB_H

#include <stdbool.h>


/*!
 * \brief Cree et lance un nouveau thread en lancant fonction sur data
 * \param fonction fonction à lancer
 * \param data paramètre de la fonction
 * \return false si la création du thread echour, true sinon
 */
bool detacheThread_sur(void*(*fonction)(void *data), void *data);


/*!
 * \brief Le type de verrou que nous allons utiliser
 */
typedef void *ptrVerrou;
/*!
 * \brief Cree un verrou
 * \return pointeurVers le verrou crée
 */
ptrVerrou creeVerrou(void);

/*!
 * \brief Ferme le verrou (s'approprie le verrou)
 * \param pVerrou
 * \return false si la demande n'a pas ete satisfaite
 */
bool fermeVerrou(ptrVerrou pVerrou);

/*!
 * \brief Ouvre le verrou (libere le verrou
 * \param pVerrou
 * \return false si l'ouverture n'a pu se fair
 */
bool ouvreVerrou(ptrVerrou pVerrou);
/*!
 * \brief Detruit le verrou
 * \param pVerrou
 */
void detruitVerrou(ptrVerrou pVerrou);

#ifndef _WIN32
// La bibliotheque propose les verrous conditionnels,  sous systeme de type POSIX pour gerer le parallelisme
/*!
 * \brief Le type de verrou conditionnel que nous allons utiliser
 */
typedef struct VerrouConditionnel *ptrVerrouConditionnel;
/*!
 * \brief Cree un verrou conditionnel
 * \return pointeur vers le verrou conditionnel
 */
ptrVerrouConditionnel creeVerrouConditionnel(void);

/*!
 * \brief Ferme le verrou conditionnel (s'approprie le verrou)
 * \param pVerrouConditionnel
 * \return false si la demande n'a pas ete satisfaite
 */
bool fermeVerrouConditionnel(ptrVerrouConditionnel pVerrouConditionnel);

/*!
 * \brief Attente sur le verrou conditionnel
 * \param pVerrouConditionnel
 * \return false si la demande n'a pas ete satisfaite
 */
bool attendVerrouConditionnel(ptrVerrouConditionnel pVerrouConditionnel);

/*!
 * \brief Envoie un signal sur le verrou conditionnel
 * \param pVerrouConditionnel
 * \return false si la demande n'a pas ete satisfaite
 */
bool signalSurVerrouConditionnel(ptrVerrouConditionnel pVerrouConditionnel);

/*!
 * \brief Envoie un signal a tous les threads en attente sur le verrou conditionnel
 * \param pVerrouConditionnel
 * \return false si la demande n'a pas ete satisfait
 */
bool signalUniverselSurVerrouConditionnel(ptrVerrouConditionnel pVerrouConditionnel);

/*!
 * \brief Ouvre le verrou conditionnel (libere le verrou)
 * \param pVerrouConditionnel
 * \return false si l'ouverture n'a pu se faire
 */
bool ouvreVerrouConditionnel(ptrVerrouConditionnel pVerrouConditionnel);
/*!
 * \brief Detruit le verrou conditionnel
 * \param pVerrouConditionnel
 */
void detruitVerrouConditionnel(ptrVerrouConditionnel pVerrouConditionnel);
#endif

#endif
