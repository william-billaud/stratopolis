/*!
   \file moteur.h
   \brief fichier contenant les prototypes des fonctions utiles pour le moteur du jeu
   \author "Billaud William"
   \date "DD"/"Month"/"Year"
*/

#include "outils.h"
#ifndef H_MOTEUR
#define H_MOTEUR

/*!
   \brief verifie qu'un coup est valide
   \param[in] "Param description"
   \return true si le coup est valide
	 \return false si le coup n'est pas possible
*/
bool estValideCoup(coup coupJoueur,PLATEAU plat);

/*!
   \brief pose une tuile sur le plateau
   \param[in] coupJoueur : coup du joueur
	 \param[in] plat : plateau de jeu sur lequelle il faut poser la pièce
   \return 1 si le coup a pu être effectué
	 \return 0 si le coup est invalide
*/
int joueCoup(coup coupJoueur,PLATEAU plat);

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
   \brief algorithmeMinMax utilisé pour faire jouer l'ia
   \param[in] "Param description"
	 TODO complete min max
   \return "Return of the function"
*/
int minMax(PLATEAU plat,int joueurActuel,int joueurIA,int ProfondeurActuelle,int ProfondeurMaximum,int *pieceDisponible,int nbPieceRestante);

/*!
   \brief dejoue un coup
   \param[in] plat : plateau de jeu
	 \param[in] coupAnnulle : coup à annullée
   \return 1 si tout c'est bien passé
	 \return -1 si le coup n'as pas pu etres annullé
*/
int dejoueCoup(PLATEAU plat,coup coupAnnulle);

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
