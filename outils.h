/*!
   \file outils.h
   \brief fichier contenant les prototypes des outils utiles dans tous les autres modules
   \author Billaud William
   \author Hipault Theo
   \date 07/02/2017

	 fichier contenant les prototypes des fonctions, les structures de données et les enumerations utiles dans les autres modules
*/

#ifndef H_OUTILS
#define H_OUTILS

#include <stdio.h>
#include <stdlib.h>		// Pour pouvoir utiliser void exit(int)
#include <math.h>		// Pour pouvoir utiliser les librairies mathematiques
#include "lib/GfxLib.h"
#include "lib/BmpLib.h"
#include <time.h>
#include <string.h>


/**
 * \brief taille maximum du tableau
 */
#define TAILLEMAX 162

/*!
   \brief enum contenant les couleurs
*/
typedef enum {
	vide /*!< case vide ( niveau 0) */ ,
	vert /*!< couleur du joueur 1 */ ,
	rouge /*!< couleur du joueur 2 */ ,
	neutre /*!< couleur neutre */ ,
} couleur;

/*!
   \brief enum contenant les orientations des pièces

	 les orientations sont données vis à vis du joueur regardant l'ecran, une pièces en L est donc en position HD
*/
typedef enum {
	HD /*!< pièce orientée avec un coté vers la haut, et l'autre vers la droite */ ,
	BD /*!< pièce orientée avec un coté vers le bas, et l'autre vers la droite */ ,
	BG /*!< pièce orientée avec un coté vers la gauche, et l'autre vers le bas */ ,
	HG /*!< pièce orientée avec un coté vers la gauche, et l'autre vers le haut */
} orientation;

/*!
   \brief structure contenant les pieces

	 Les informations concernant les couleurs sont données pour la pièce positionnée en L
*/
typedef struct pieces {
	couleur c1;		/*!< couleur de la case du haut  */
	couleur c2;		/*!< couleur de la case du milieu */
	couleur c3;		/*!< couleur de la case  a droite */
	unsigned int numeroPiece;	/*!< numero de la pièce */
} pieces;
/*!
   \brief structure contenant des informations concernant un étage d'une case
*/
typedef struct etage {
	unsigned int numeroPiece;	/*!< numero de la pièce , 42 correspond à une absence de pièces */
	couleur couleurEtage;	/*!< couleur de la piece sur case */
} etage;

/*!
\brief structure contenant toutes les couches de la case

tabEtage[hauteur] correspond à la pièce visible
*/
typedef struct historiqueCase {
	int hauteur;		/*!< hauteur de la case (0 si la case est vide) */
	etage tabEtage[20];	/*!< tableau contenant tous les étages de la case */
	int x;
	   /**< abscisse de la case dans le plateau*/
	int y;
	   /**< ordonnée de la case dans le plateau*/
} historiqueCase;

/*!
   \brief structure contenant les informations pour jouer un coup
*/
typedef struct coup {
	unsigned int numeroPiece;	/*!< numero de la pièce à jouer */
	unsigned int xCoup;	/*!< abscisse de la case centrale de la pièce (C2) */
	unsigned int yCoup;	/*!< ordonnee de la case centrale de la pièce (C2) */
	orientation orientationPiece;	/*!< orientation de la pièce */
} coup;

/*!
 * \brief tableau contenant l'ordre des pièces
 */
typedef int ORDREPIECE[21];

/*!
 * \brief tableau contenant le plateau de jeu
 */
typedef historiqueCase PLATEAU[TAILLEMAX][TAILLEMAX];

/*!
\brief retourne la couleur d'une case
\param[in] c : case dont la couleur est demandée
\return couleur de la case
\return -1 en cas d'erreur
*/
int getCouleurCase(historiqueCase * c);

/*!
\brief retourne la hauteur d'une case
\param[in] c : pointeur vers la case dont la hauteur est demandée
\return hauteur de la case, -1 en cas d'erreur
*/
int getHauteurCase(historiqueCase * c);

/*!
\brief fonction permettant de recuperer un pointeur vers un case
\param[in] x : abscisse de la case
\param[in] y : ordonée de la case
\return NULL si la case n'est pas disponible
\return historiqueCase contenant les informations de la case
*/
historiqueCase *getCase(int x, int y);

/*!
 * \brief initialise tout les paramètres d'une case a 0
 * \param c : pointeur vers une case
 * \return 0
 */
int setCaseAZero(historiqueCase * c);

/*!
 * \brief fonction permettant de récuperer le numero de la pièce en haut d'une case
 * \param c : case dont nous voulons récuperer le numero de la pièce
 * \return -2 : si la hauteur de la case est incorrecte
 * \return -1 : si le numero de la case est incorrecte
 * \return 42 si la case ne possède pas de pièce
 */
int getNumeroPiece(historiqueCase * c);

/*!
 * \brief retourne la couleur d'une pièce
 * \param numeroPiece : numero de la pièce
 * \param numeroTuile : numero de la tuile sur la pièce ( 1, 2 ou 3)
 * \return la couleur correspondant au numero de la pièce
 * \return neutre en cas d'erreur
 */
couleur couleurPiece(int numeroPiece, int numeroTuile);

/*!
 * \brief initalise les pièces du jeu dans un tableau
 * \return 0 si tout s'est bien passé
 */
int initPiece(void);

/*!
 * \brief retourne une case d'un coup
 * \param coupJoueur : coup du joueur
 * \param [out] tab : tableau contenant les cases
 * \return -1 si une case contient un pointeur null
 * \return 0 si tout s'est bien passé
 */
int getCasesFromCoup(coup coupJoueur, historiqueCase * tab[3]);

/*!
 * \brief calcule le minimum entre deux valeurs
 * \param a
 * \param b
 * \return le minimum entre a et b
 */
int min(int a, int b);

/*!
 * \brief retourne le maximum entre a et b
 * \param a
 * \param b
 * \return le maximum entre a et b
 */
int max(int a, int b);

/*!
 * \brief trouve le meilleur zooom pour le cadrage actuel
 * \param [out] x : pointeur vers l'abscisse du meilleur zoom
 * \param [out] y : pointeur vers l'ordonnée du meilleur zoom
 * \param [out] zoom : pointeur vers le meilleur zoom
 * \return -1 en cas d'erreur
 * \return 0 si non
 */
int trouveMeilleurZoom(unsigned int *x, unsigned int *y, unsigned int *zoom);


/*!
 * \brief fonction permettant de gèrer le temp
 * \param ordre : 0 pour reinitialiser le temp stocké n°1
 * \param ordre : 1 pour renvoie le temp stocké n°1
 * \param ordre : 2 pour reinitialiser le temp stocké n°2
 * \param ordre : 3 pour renvoie le temp stocké n°2
 * \param ordre : 4 pour reinitialiser le temp stocké n°3
 * \param ordre : 5 pour renvoie le temp stocké n°3
 * \param ordre : 6 pour activer la pause
 * \param ordre : 7 pour desactiver la pause
 * \return le temp stocké
 * \return 0 si il a été reinitialisé
 */
int gestionDuree(int ordre);

//definition des variables globales

PLATEAU plat;
/**< variable globale contenant le plateau*/

ORDREPIECE ordreJoueurs[2];
/**< tableau contenant l'ordre des pièces des joueurs 1 et 2, ordreJoueur[0]= ordre des pièces du joueur 1
 * ordreJoueur[1]= ordre des pièces du joueur 2*/

pieces PIECE[42];
/**< tableau contenant les pièces */

#endif
