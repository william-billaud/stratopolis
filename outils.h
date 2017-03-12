/*!
   \file outils.h
   \brief fichier contenant les prototypes des outils utiles dans tous les autres modules
   \author Billaud William
   \author Hipault Theo
   \date \today

	 fichier contenant les prototypes des fonctions,les structures de données et les enum utiles dans les autres modules
*/

#ifndef H_OUTILS
#define H_OUTILS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>		// Pour pouvoir utiliser void exit(int)
#include <math.h>		// Pour pouvoir utiliser les librairies mathematiques
#include "lib/ESLib.h"
#include "lib/GfxLib.h"
#include <time.h>

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

	 les orientations sont données vis a vis du joueur regardant l'ecran, une pièces en L est donc en position HD
*/
typedef enum {
	HD /*!< pièce orientée avec un coté vers la haut, et l'autre vers la droite */ ,
	BD /*!< pièce orientée avec un coté vers le bas, et l'autre vers la droite */ ,
	BG /*!< pièce orientée avec un coté vers la gauche, et l'autre vers le bas */ ,
	HG			/*!< pièce orientée avec un coté vers la gauche, et l'autre vers le haut */
} orientation;

/*!
   \brief structure contenant les pieces

	 Les informations concernant les couleur sont données pour la pièce positionnée en L
*/
typedef struct pieces {
	couleur c1;		/*!< couleur de la case du haut  */
	couleur c2;		/*!< couleur de la case du milieu */
	couleur c3;		/*!< couleur de la case  a droite */
	unsigned char numeroPiece;	/*!< numero de la pièce */
} pieces;
/*!
   \brief structure contenant des informations concernant un étage d'une case
*/
typedef struct etage {
	unsigned char numeroPiece;	/*!< numero de la pièce , 42 correspond à une absence de pièces */
	couleur couleurEtage;	/*!< couleur de la pieces sur case */
} etage;

/*!
\brief structure contenant toutes les couches de la case

tabEtage[hauteur] correspond à la pièce visible
*/
typedef struct historiqueCase {
	char hauteur;		/*!< hauteur de la case (0 si la case est vide) */
	etage tabEtage[20];	/*!< tableau contenant tous les étages de la case */
	int x;
	int y;
} historiqueCase;

/*!
   \brief structure contenant les informations pour jouer un coup
*/
typedef struct coup {
	unsigned char numeroPiece;	/*!< numero de la pièces à jouer */
	unsigned int xCoup;	/*!< abscisse de la case central de la pièces (C2) */
	unsigned int yCoup;	/*!< ordonnee de la case central de la pièces (C2) */
	orientation orientationPiece;	/*!< orientation de la pièce */
} coup;

/*!
 * \brief tableau contenant l'ordre des pièces
 */
typedef int ORDREPIECE[20];

/*!
 * \brief tableau contenant le plateau de jeu
 */
typedef historiqueCase PLATEAU[TAILLEMAX][TAILLEMAX];

/*!
\brief retourne la couleur d'une case
\param[in] c  case dont la couleur est demandé
\return couleur de la case
\return -1 en case d'erreur
*/
int getCouleurCase(historiqueCase c);

/*!
\brief retourne la hauteur d'une case
\param[in] c case dont la hauteur est demandé
\return hauteur de la case, -1 en case d'erreur
*/
int getHauteurCase(historiqueCase c);

/*!
\brief fonction permettant de recuperer un pointeur vers un case
\param[in] x : abscisse de la case
\param[in] y : ordonée de la case
\return NULL si la case n'est pas disponible
\return historiqueCase contenant les informations de la case
*/
historiqueCase *getCase(int x, int y);

/*!
 * \brief initialise tout les paramètre d'une case a 0
 * \param c pointeur vers une case
 * \return 0
 */
int setCaseAZero(historiqueCase * c);

/*!
 * \brief fonction permettant de récuperer le numero de la pièce en haut d'une case
 * \param c case dont nous voulons récuperer le numero de la pièce
 * \return -2 : si la hauteur de la case est incorecte
 * \return -1 : si le numero de la case est incorecte
 * \return 42 si la case ne possède pas de pièce
 */
int getNumeroPiece(historiqueCase c);

/**
 * \brief verifie si une valeur est present dans un tableau 1D d'entier
 * \param array tableau dans lequel il faut chercher la valeur
 * \param h taille du tableau
 * \param valeur valeur a chercher
 * \return false si la valeur est absent
 * \return true si la valeur est presente
 * \warning si le tableau n'a pas été initialisé entièrement, la valeur peut etres présente dans la partie non initialisée
 * \warning si h est trop grand, il y a un risque de core dumped
 */
bool inArrayIny(int *array, unsigned int h, int valeur);


/*!
 * \brief retourne la couleur d'une pièce
 * \param numeroPiece numero de la pièce
 * \param numeroTuile numero de la tuile sur la pièce ( 1, 2 ou 3)
 * \return la couleur correspondant au numero de la pièce
 * \return neutre en cas d'erreur
 */
couleur couleurPiece(int numeroPiece, int numeroTuile);

/*!
 * \brief initalise les pièces du jeu dans un tableau
 * \return 0 si tout c'est bien passé
 */
int initPiece(void);

/*!
 * \brief retourne une case d'un coup
 * \param coupJoueur coup du joueur
 * \param [out] tableau contenant les cases
 * \return -1 si une case contient un pointeur null
 * \return 0 si tout c'est bien passé
 */
int getCasesFromCoup(coup coupJoueur, historiqueCase * tab[3]);

//definition des variables globales
/**\var variable global contenant le plateau*/
PLATEAU plat;

/**\var tableau contenant l'ordre des pièces de joueurs 1 et 2, ordreJoueur[0]= ordre des pièces du joueur 1
 * ordreJoueur[1]= ordre des pièces du joueur 2*/
ORDREPIECE ordreJoueurs[2];
/*!
 * \brief tableau contenant les pièces.
 */
pieces PIECE[42];
#endif
