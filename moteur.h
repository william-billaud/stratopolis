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
 * \brief structure contenant les informations pour créer une liste de cases adjacentes
 */
typedef struct caseCalcul {
	int x /**< abscisse de la case*/ ;
	int y /**< ordonnée de la case*/ ;
	int hauteur /**< hauteur de la case*/ ;
	struct caseCalcul *next
    /**< pointeur vers une autre case appartenant au meme bloc*/ ;
} caseCalcul;

/*!
 * \brief structure servant a créer une liste des blocs de cases differentes
 */
typedef struct listeBlock {
	caseCalcul *debutBlock /**< debut du bloc de case de la meme couleur adjacente*/ ;
	struct listeBlock *next /**< pointeur vers le bloc suivant */ ;
} listeBlock;

/*!
 * \brief verifie qu'un coup est valide
 * \param[in] coupJoueur : coup du joueur
 * \return true si le coup est valide
 * \return false si le coup n'est pas possible
 */
bool estValideCoup(coup coupJoueur);

/*!
 * \brief pose une tuile sur le plateau
 * \param[in] coupJoueur : coup du joueur
 * \return 1 si le coup a pu être effectué
 * \return 0 si le coup est invalide
 * \return -1 en cas d'erreur
 */
int joueCoup(coup coupJoueur);

/*!
 * \brief calcule le score d'un joueur
 * \param[in] joueur : numero du joueur
 * \return score du joueur
 * \return -1 en cas d'erreur
 */
int calculScore(int joueur);

/*!
 * \brief recherche si la case possède une tuile adjacente
 * \param[in] x : ordonnee de la case
 * \param[in] y : abscisse de la case
 * \return true si la case possede une tuile adjacente
 * \return false si la case ne possède pas de tuile adjacente
 */
bool possedeTuileAdjacente(int x, int y);


/*!
 * \brief dejoue un coup
 * \param[in] coupAnnule : coup à annuler
 * \return 1 si tout s'est bien passé
 * \return -1 si le coup n'as pas pu être annulé
 */
int dejoueCoup(coup coupAnnule);

/*!
 * \brief initialise le plateau (pose la pièce initiale)
 * \return 0 si tout s'est bien passé
 * \return -1 si un problème a eu lieu
 */
int initPlateau(void);

/*!
 * \brief choisis le joueur qui commence
 * \return 1 si le joueur 1 commence
 * \return 2 si le joueur 2 commence
 */
int choisisJoueur(void);

/*!
 * \brief initialise l'ordre des pièces dans un tableau
 * \param[in] joueur numero du joueur
 * \return 0 si la fonctions n'a pas eu de problème pour s'effectuer
 * \return -1 si il y a eu une erreur
 */
int initOrdrePieces(int joueur);

/*!
 * \brief permet de savoir si une superposition de couleur est valide
 * \param[in] haut : pièce du haut
 * \param[in] bas : pièce du bas
 * \return true si la superposition est valide
 * \return false si la superpostion est invalide
 */
bool estValideSuperposition(couleur haut, couleur bas);

/*!
 * \brief fonction permettant de savoir si un couple de coordonées est present dans une liste simplement chainée
 * \param[in] x : abscisse à tester
 * \param[in] y : ordonnée à tester
 * \param[in] caseDebut : tête de la liste
 * \return true si le couple est présent dans la liste
 * \return false si le couple n'est pas présent dans la liste
 */
bool estDansBlock(int x, int y, caseCalcul * caseDebut);

/*!
 * \brief ajoute une caseCalcul en debut de ligne et initialise ses valeurs
 * \param[in] tete : pointeur de le tête precedente
 * \param[in] x : abscisse de la case
 * \param[in] y : ordonnée de la case
 * \param[in] hauteur : hauteur de la case
 * \return pointeur vers la nouvelle tete
 */
caseCalcul *ajouteCaseCalcul(caseCalcul * tete, int x, int y, int hauteur);

/*!
 * \brief fonction libérant une liste de caseCalcul
 * \param tete : tête de la liste à libérer
	*/
void libereCaseCalcul(caseCalcul * tete);

/*!
 * \brief calcule le score donné par une liste
 * \param[in] tete : tête de la liste
 * \return score de la liste
 */
int scoreListe(caseCalcul * tete);

/*!
 * \brief concatène deux listes de caseCalcul dans listeBlock et libère la case ainsi libérée
 * \param[in,out] block : listeBlock dans laquelle il faut concatener les liste de caseCalcul
 * \param[in] listeA
 * \param[in] listeB : liste à ajouter a la fin de listeA
 */
void concateneCaseCalcul(listeBlock * block, caseCalcul * listeA,
			 caseCalcul * listeB);

/*!
 * \brief
 * \param[out] joueur : pointeur vers un entier contenant le joueur qui commencera
 * \return -1 si l'initation des pièce du joueur 1 a eu un problème
 * \return -2 si l'initiation des pièces du joueur 2 a eu un problème
 * \return -4 si le plateau a été mal initialisé
 * \return somme des retour precedents ( à la manière du chmod)
 */
int initPartie(int *joueur);

/*!
 * \brief trouve un coup aleatoire pour le joueur
 * \param[in] joueur
 * \return un coup aleatoire valide
 */
coup coupAleatoire(int joueur);
#endif
