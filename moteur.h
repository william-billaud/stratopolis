/*!
   \file moteur.h
   \brief fichier contenant les prototypes des fonctions utiles pour le moteur du jeu
   \author Billaud William
   \author Hipault Theo
   \date 22/01/2017
*/

#include "outils.h"
#ifndef H_MOTEUR
#define H_MOTEUR

/*!
\brief verifie qu'un coup est valide
\param[in] coupJoueur coup du joueur
\return true si le coup est valide
\return false si le coup n'est pas possible
*/
bool estValideCoup(coup coupJoueur);

/*!
\brief pose une tuile sur le plateau
\param[in] coupJoueur : coup du joueur
\return 1 si le coup a pu être effectué
\return 0 si le coup est invalide
*/
int joueCoup(coup coupJoueur);

/*!
\brief calcul le score d'un joueur
\param[in] joueur : numero du joueur
\return score du joueur
\return -1 en cas d'erreur
*/
int calculScore(int joueur);

/*!
\brief recherche si la case possède une tuile adjacente
\param x : ordonnee de la case
\param y : abscisse de la case
\return true si la case possede une tuile adjacente
\return false si la case ne possède pas de tuile adjacente
*/
bool possedeTuileAdjacente(int x, int y);

/*!
\brief cherche un coup pour l'ia
\param[in] joueur : joueur jouer par l'ia
\param[in] niveauDifficulte : niveau de difficulté de l'ia
\param[in] piecesDisponible : liste des pièces disponible
\param[in] nbPieceRestante : nombre de pièces restantes
\return un coup proposé par l'ia
*/
coup coupIA(int joueur, int niveauDifficulte, int *pieceDisponible,
	    int nbPieceRestante);

/*!
 * \brief algorithme min max
 * \param joueurActuel joueur qui doit jouer
 * \param joueurIA joueur remplacé par l'IA
 * \param ProfondeurActuelle nombre de recursion
 * \param ProfondeurMaximum nom de recursion maximum
 * \param[out] meilleurCoup
 * \return score de la situation
 */
int minMax(int joueurActuel, int joueurIA, int ProfondeurActuelle,
	   int ProfondeurMaximum, coup * meilleurCoup);

/*!
 * \brief dejoue un coup
 * \param[in] coupAnnulle : coup à annullée
 * \return 1 si tout c'est bien passé
 * \return -1 si le coup n'as pas pu etres annullé
*/
int dejoueCoup(coup coupAnnulle);

/*!
 * \brief initialise le plateau (pose la pièce initiale)
 * \return 0 si tout c'est bien passé
 * \return -1 si un problème a eu lieu
 */
int initPlateau(void);

/*!
 * \brief choisis le joueur qui commenceras
 * \return 1 si le joueur 1 commenceras
 * \return 2 si le joueur 2 commenceras
 */
int choisisJoueur(void);

/*!
 * \brief initialise l'ordre des pièces dans un tableau
 * \param joueur numero du joueur
 * \return 0 si la fonctions n'a pas eu de problème pour s'effectuer
 * \return -1 si il y a eu une erreur
 */
int initOrdrePieces(int joueur);

/*!
 * \brief permet de savoir si une superposition de couleur est valide
 * \param haut pièce du haut
 * \param bas pièce du bas
 * \return true si la superposition est valide
 * \return false si la superpostion est invalide
 */
bool estValideSuperposition(couleur haut, couleur bas);
#endif
