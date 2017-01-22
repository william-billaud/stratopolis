/*!
   \file moteur.h
   \brief fichier contenant les prototypes des fonctions utiles pour le moteur du jeu
   \author "Billaud William"
   \date "DD"/"Month"/"Year"
*/

#include "outils.h"
#include <stdlib.h>
#include <stdbool.h>
#ifndef H_MOTEUR
#define H_MOTEUR

/*!
   \brief verifie qu'un coup est valide
   \param[in] coupJoueur coup du joueurs
   \param[in] plat  plateau de jeu
   \return true si le coup est valide
   \return false si le coup n'est pas possible
*/
bool estValideCoup(coup coupJoueur,PLATEAU plat);

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
int calculScore(PLATEAU plat,int joueur);

/*!
   \brief recherche si la case possède une tuile adjacente
   \param[in] plat : plateau de jeu
	 \param x : ordonnee de la case
	 \param y : abscisse de la case
   \return true si la case possede une tuile adjacente
	 \return false si la case ne possède pas de tuile adjacente
*/
bool possedeTuileAdjacente(PLATEAU plat,int x,int y);

/*!
   \brief cherche un coup pour l'ia
   \param[in] plat : plateau de jeu
	 \param[in] joueur : joueur jouer par l'ia
	 \param[in] niveauDifficulte : niveau de difficulté de l'ia
	 \param[in] piecesDisponible : liste des pièces disponible
	 \param[in] nbPieceRestante : nombre de pièces restantes
   \return un coup proposé par l'ia
*/
coup coupIA(PLATEAU plat,int joueur,int niveauDifficulte,int *pieceDisponible,int nbPieceRestante);

/*!
 * \brief
 * \param plat
 * \param joueurActuel
 * \param joueurIA
 * \param ProfondeurActuelle
 * \param ProfondeurMaximum
 * \param pieceDisponible
 * \param nbPieceRestante
 * \return
 */
int minMax(PLATEAU plat,int joueurActuel,int joueurIA,int ProfondeurActuelle,int ProfondeurMaximum,int *pieceDisponible,int nbPieceRestante);

/*!
   \brief dejoue un coup
	 \param[in] coupAnnulle : coup à annuller
   \return 1 si tout c'est bien passé
   \return -1 si le coup n'as pas pu etres annullé
*/
int dejoueCoup(coup coupAnnulle);

/*!
   \brief Initialise une nouvelle partie avec les paramètres choisis
   \param[in] aucun
	 \return -1 en cas d'erreur
   \return 0 si tout est initialisé correctement
*/
int initialise();

/*!
   \brief Initialise toutes les cases du plateau à « vide », et efface l’historique des coups de chaque case
   \param[in] aucun
	 \return -1 en cas d'erreur
   \return 0 si tout est initialisé correctement
*/
int iniPlateau();

/*!
   \brief Initialise les listes de pièces disponibles pour les deux joueurs
   \param[in] aucun
	 \return -1 en cas d'erreur
   \return 0 si tout est initialisé correctement
*/
int initialiseOrdrePieces();

/*!
   \brief Choisis un joueur aléatoire
   \param[in] aucun
	 \return un nombre aléatoire entre 1 et 2
*/
int choisisJoueur();

/*!
   \brief Appelle les fonctions coupIA() et afficheConseil()
   \param[in] aucun
	 \return -1 en cas d'erreur
   \return 0 si tout est affiché correctement
*/
conseille();

/*!
   \brief Calcule la surface d’une zone à partir d’une case spécifiée
   \param[in] posX : position en abscisse de la case de départ
   \param[in] posY : position en ordonnée de la case de départ
	 \param[in] plat : plateau de jeu à analyser
	 \return -1 en cas d'erreur
   \return le nombre de cases adjacentes
*/
int calculSurface(int posX, int posY, PLATEAU plat);

/*!
   \brief Calcule la hauteur maximum d’une zone à partir d’une case spécifiée
   \param[in] posX : position en abscisse de la case de départ
   \param[in] posY : position en ordonnée de la case de départ
   \param[in] plat : plateau de jeu à analyser
   \return -1 en cas d'erreur
   \return la hauteur maximum de la zone
*/
int calculHauteur(int posX, int posY, PLATEAU plat);


/*!
 * \brief initialise le plateau
 * \param plat plateau a initialisé
 * \return 0 si tout c'est bien passé
 * \return -1 si un problème a eu lieu
 */
int initPlateau(PLATEAU plat);

/*!
   \brief Initialise une nouvelle partie avec les paramètres choisis
   \param[in] nom : desc
	 \param[in]
   \return
	 \return
*/
initialise();

/*!
   \brief Initialise toutes les cases du plateau à « vide », et efface l’historique des coups de chaque case
   \param[in] nom : desc
	 \param[in]
   \return
	 \return
*/
iniPlateau();

/*!
   \brief Initialise les listes de pièces disponibles pour les deux joueurs
   \param[in] nom : desc
	 \param[in]
   \return
	 \return
*/
initialiseOrdrePieces();

/*!
   \brief Choisis un joueur aléatoire
   \param[in] nom : desc
	 \param[in]
   \return
	 \return
*/
choisisJoueur();

/*!
   \brief Appelle les fonctions coupIA() et afficheConseil()
   \param[in] nom : desc
	 \param[in]
   \return
	 \return
*/
conseille();

/*!
   \brief Calcule la surface d’une zone à partir d’une pièce spécifiée
   \param[in] nom : desc
	 \param[in]
   \return
	 \return
*/
calculSurface();

/*!
   \brief Calcule la hauteur maximum d’une zone à partir d’une pièce spécifiée
   \param[in] nom : desc
	 \param[in]
   \return
	 \return
*/
calculHauteur();

#endif
