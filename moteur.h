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
 * \brief structure contenant les information pour crée une liste de case adjacente
 */
typedef struct caseCalcul {
	int x /**< abscisse de la case*/ ;
	int y /**< ordonnée de la case*/ ;
	int hauteur /**< hauteur de la case*/ ;
	struct caseCalcul *next
    /**< pointeur vers une autre case appartenant au meme block*/ ;
} caseCalcul;

/*!
 * \brief structure servant a crées une liste des block de cases differents
 */
typedef struct listeBlock {
	caseCalcul *debutBlock /**< debut du block de case de la meme couleurs adjacent*/ ;
	struct listeBlock *next /**< pointeur vers le block suivant */ ;
} listeBlock;

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
\return -1 en cas d'erreur
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

/*!
 * \brief fonction permettant de savoir si un couple de coordonée est present dans une liste simplement chainée
 * \param x abscisse à tester
 * \param y ordonée à tester
 * \param caseDebut tête de la liste
 * \return true si le couple est present dans la liste
 * \return false si le couple n'est pas present dans la liste
 */
bool estDansBlock(int x, int y, caseCalcul * caseDebut);

/*!
 * \brief ajoute une caseCalcul en debut de ligne et initialise ses valeurs
 * \param tete pointeur de le tête precedente
 * \param x abscisse de la case
 * \param y ordonnée de la case
 * \param hauteur hauteur de la case
 * \return pointeur vers la nouvelle tete
 */
caseCalcul *ajouteCaseCalcul(caseCalcul * tete, int x, int y, int hauteur);

/*!
 * \brief fonction liberant une liste de caseCalcul
 * \param tete tete de la liste à libérer
 */
void libereCaseCalcul(caseCalcul * tete);

/*!
 * \brief calcul le score donnée par une liste
 * \param tete tete de la liste
 * \return score de la liste
 */
int scoreListe(caseCalcul * tete);

/*!
 * \brief concatene deux liste de caseCalcul dans listeBlock et libère la case ainsi libere
 * \param block listeBlock dans laquelle il faut concatener les liste de caseCalcul
 * \param listeA
 * \param listeB liste à ajouter a la fin de listeA
 */
void concateneCaseCalcul(listeBlock * block, caseCalcul * listeA,
			 caseCalcul * listeB);
/*!
 * \brief
 * \param joueur joueur pointeur vers un entier contenant le joueur qui commenceras
 * \return -1 si l'initation des pièce du joueur 1 a eu un problème
 * \return -2 si l'initiation des pièces du joueur 2 à eu un problème
 * \return -4 si le plateau à été mal initialisé
 * \return somme des retour precedent ( à la manière du chmod)
 */
int initPartie(int *joueur);

#endif
