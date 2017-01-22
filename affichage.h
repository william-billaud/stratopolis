/*!
   \file affichage.h
   \brief fichier contenant les prototypes des fonctions pour l'affichage du jeu
   \author Hipault Theo
   \date 22/01/2017
*/
#include "outils.h"

#ifndef H_AFFICHAGE
#define H_AFFICHAGE

/*!
   \brief Affiche le menu principal (Jouer, Aide, Options, Quitter), et la sélection
   \param[in] posX : position en abscisse du curseur de la souris
	 \param[in] posY : position en ordonnée du curseur de la souris
   \return 0 si le curseur ne survole aucun bouton
   \return 1 si le curseur survole le bouton Jouer
   \return 2 si le curseur survole le bouton Aide
   \return 3 si le curseur survole le bouton Options
   \return 4 si le curseur survole le bouton Quitter
*/
int afficheMenu(int posX, int posY);

/*!
   \brief Affiche les règles du jeu et le mode d’emploi du programme, et la sélection
   \param[in] posX : position en abscisse du curseur de la souris
	 \param[in] posY : position en ordonnée du curseur de la souris
   \return 0 si le curseur ne survole aucun bouton
   \return 1 si le curseur survole le bouton Retour
*/
int afficheAide(int posX, int posY);

/*!
   \brief Affiche le menu de sélection des options, et la sélection
   \param[in] posX : position en abscisse du curseur de la souris
	 \param[in] posY : position en ordonnée du curseur de la souris
   \return 0 si le curseur ne survole aucun bouton
   \return 1 si le curseur survole le bouton Retour
*/
int afficheOption(int posX, int posY);


/*!
   \brief Affiche un conseil pour un coup
   \param[in] conseil : coup à afficher
   \return rien
*/
void afficheConseil(coup conseil);

/*!
   \brief Appelle les fonction dessinePredictif() et estValideCoup()
   \param[in] coupJoueur : coup à afficher
   \return rien
*/
void affichePredictif(coup coupJoueur);

/*!
   \brief Affiche le prédictif de placement de la pièce
   \param[in] coupJoueur : coup à afficher
	 \param[in] estValide : validité du coup à afficher
   \return
*/
void dessinePredictif(coup coupJoueur, bool estValide);

/*!
   \brief Affiche l’interface de jeu
   \param[in] nomJ1 : nom du premier joueur
	 \param[in] nomJ2 : nom du deuxième joueur
	 \return rien
*/
void afficheInterface(char nomJ1[15], char nomJ2[15]);

/*!
   \brief Affiche le plateau de jeu, la couleur et la hauteur de chaque case
   \param[in] plat : plateau de jeu à afficher
	 \return rien
*/
void afficheGrille(int Xdroite,int XGauche,int YBas,int YHaut );

/*!
   \brief Affiche le score
   \param[in] scoreJ1 : score du premier joueur
	 \param[in] scoreJ2 : score du deuxième joueur
	 \return rien
*/
void afficheScore(int scoreJ1, int scoreJ2);

/*!
   \brief Met le jeu en pause
   \param[in] aucun
   \return rien
*/
pause();

#endif
