/*!
   \file affichage.h
   \brief fichier contenant les prototypes des fonctions pour l'affichage du jeu
   \author Hipault Theo
   \author Billaud
   \date 22/01/2017
*/
#include "outils.h"
#include "moteur.h"

#ifndef H_AFFICHAGE
#define H_AFFICHAGE

/*!
 * \brief Affiche le menu principal (Jouer, Aide, Options, Quitter), et la sélection
 * \return rien
 */
void afficheMenu(void);

/*!
 * \brief Affiche les règles du jeu et le mode d’emploi du programme, et la sélection
 * \return rien
 */
void afficheAide(void);

/*!
 * \brief Affiche le menu de sélection des options, et la sélection
 * \param[in] limiteTemp indique si la limite de temp est activée
 * \param[in] dureeLimite indique la durée maximum d'un tour
 * \param[in] niveauDifficulte indique le niveau de difficulté (entre 0 et 4)
 * \param[in] modeSuivant indique le mode de jeu actuel
 * \return rien
 */
void afficheOption(bool limiteTemp, unsigned int dureeLimite, int niveauDifficulte, int modeSuivant);

/*!
 * \brief Appelle les fonction dessinePredictif() et estValideCoup()
 * \param[in] coupJoueur : coup à afficher
 * \param[in] zoom de la grille
 * \return rien
	*/
void affichePredictif(coup coupJoueur, int zoom);

/*!
 * \brief Affiche le prédictif de placement de la pièce
 * \param[in] coupJoueur : coup à afficher
 * \param[in] estValide : validité du coup à afficher
 * \param[in] zoom zoom de la grille
 * \return
	*/
void dessinePredictif(coup coupJoueur, bool estValide, int zoom);

/*!
 * \brief Affiche l’interface de jeu
 * \param[in] nomJ1 : nom du premier joueur
 * \param[in] nomJ2 : nom du deuxième joueur
 * \param[in] joueurActuelle : joueur dont c'est le tour
 * \return rien
 */
void afficheInterface(char nomJ1[15], char nomJ2[15], int joueurActuelle);

/*!
 * \brief Affiche le plateau de jeu, la couleur et la hauteur de chaque case
 * \param[in] zoom : nombre de case affiché par ligne/colonne
 * \param[in] basX : abscisse de la case du bas
 * \param[in] basY : abscisse de la case du bas
 */
void afficheGrille(unsigned int zoom, unsigned int basX, unsigned int basY);

/*!
 * \brief Affiche une case d'une pièce
 * \param [in] couleurCase : couleur de la case à afficher
 * \param [in] hauteurCase : hauteur de la case à afficher
 * \param [in] minX : coordonnee minimum en abscisse où afficher la case
 * \param [in] minY : coordonnee minimum en ordonnée
 * \param [in] maxX : coordonnee maximum en abscisse
 * \param [in] maxY : coordonnee maximum en ordonée
 * \param [in] estGrisee : determine si la case doit être grisée (true) ou non (false)
 */
void afficheCase(couleur couleurCase, int hauteurCase, float minX, float minY,
		 float maxX, float maxY, bool estGrisee);

/*!
  * \brief Affiche une case d'une pièce
  * \param [in] numeroPiece : numero de la pièce à afficher
  * \param [in] orientationPiece : orientation de la pièce
  * \param [in] minX : coordonnee minimum en abscisse où afficher la case
  * \param [in] minY : coordonnee minimum en ordonnée
  * \param [in] maxX : coordonnee maximum en abscisse
  * \param [in] maxY : coordonnee maximum en ordonée
  * \param [in] estGrisee : determine si la case doit être grisée (true) ou non (false)
   */
void affichePiece(int numeroPiece, orientation orientationPiece, int minX,
		  int minY, int maxX, int maxY, bool estGrisee);

/*!
 * \brief Affiche les contours d'une case
 * \param [in] numC : numéro de la case
 * \param [in] numH : numéro de la case du haut
 * \param [in] numD : numéro de la case de droite
 * \param [in] numB : numéro de la case du bas
 * \param [in] numG : numéro de la case de gauche
 * \param [in] centreY : coordonnee en ordonnee du centre de la case
 * \param [in] centreX : coordonnee en abscisse du centre de la case
 * \param [in] taille_case : taille des cases
  */
void afficheBorduresDeCase(int numC, int numH, int numD, int numB, int numG,
			   float centreX, float centreY, float taille_case);

/*!
 * \brief Affiche la séparation entre deux cases de pièces différentes
 * \param [in] numero1 : numéro de la première case
 * \param [in] numero2 : numéro de la deuxième case
 * \param [in] centreX1 : coordonnee en abscisse du centre de la première case
 * \param [in] centreY1 : coordonnee en ordonnee du centre de la première case
 * \param [in] centreX2 : coordonnee en abscisse du centre de la deuxième case
 * \param [in] centreY2 : coordonnee en ordonnee du centre de la deuxième case
  */
void afficheBordureEntreCases(int numero1, int numero2, float centreX1,
			      float centreY1, float centreX2, float centreY2);

/*!
 * \brief Affiche le score
 * \param [in] scoreJ1 : score du premier joueur
 * \param [in] scoreJ2 : score du deuxième joueur
	*/
void afficheScore(int scoreJ1, int scoreJ2);

/*!
 * \brief donne les coordonées dans le plateau des coordonnée de la souris
 * \param[out] x : abscisse de la casse ou la souris est
 * \param[out] y : ordonnée de la casse ou la souris est
 * \param[in] zoom : zoom de la grille
 * \param[in] basX : plus petite abscisse affichée
 * \param[in] basY : plus petite ordonnée affichée
 * \return 0 si l'utilisateur a clique dans la grille
 * \return 1 si l'utilisateur à clique dans la zone de selection du joueur 1
 * \return 2 si l'utilisateur à clique dans la zone de selection du joueur 3
 * \return 3 si l'utilisateur clic dans la zone du bouton Pause
 * \return 4 si l'utilisateur clic dans la zone du bouton Aide
 * \return 5 si l'utilisateur clic dans la zone du bouton Quitter
	*/
int detecteCase(int *x, int *y, int zoom, unsigned int basX, unsigned int basY);

/*!
 * \brief appelle couleurCourante() en fonction du paramètre
 * \param [in] couleurCase : couleur de la case à déterminer
 * \param [in] estGrisee : determine si la couleur doit être grisée (true) ou non (false)
 * \return rien
	*/
void determineCouleur(couleur couleurCase, bool estGrisee);

/*!
 * \brief change le zoom de la grille
 * \param [out] x_z : nouveau x minimum du zoom
 * \param [out] y_z : nouveau y minimum du zoom
 * \param [out] zoom : nouveau zoom
 * \param [in] up : true si c'est un zoom, false si c'est un dezoom
	*/
void changeZoom(unsigned int *x_z, unsigned int *y_z, unsigned int *zoom,
		bool up);
/*!
 * \brief affiche la durée de la partie depuis le debut de la partie
 * \param taille : taille des interfaces à afficher
	*/
void afficheDuree(int taille);

/*!
 * \brief fonction permettant de savoir si le clic est dans un rectangle
 * \param[in] xClic : abscisse du clic
 * \param[in] yClic : ordonnée du clic
 * \param[in] xMin : abscisse minimum du rectangle
 * \param[in] yMin : ordonnée minimum du rectangle
 * \param[in] xMax : abscisse maximum du rectangle
 * \param[in] yMax : ordonnee maximum du rectangle
 * \return true si le clic est dans le rectangle
 * \return false si le clic n'est pas dans le rectangle
 */
bool estDansRectangle(int xClic,int yClic,int xMin,int yMin,int largeur,int hauteur);

/*!
 * \brief detecte la zone de clic du menu principale
 * \return 1 : jouer
 * \return 2 : option
 * \return 3 : aide
 * \return 4 : quitter
	*/
int detecteMenuPrincipal(void);

/*!
 * \brief detecte la zone de clic du menu des options
 * \return 1 : mode de jeu
 * \return 2 : limite de temps
 * \return 3 : difficulté IA
 * \return 4 : changer de noms
 * \return 5 : retour
	*/
int detecteMenuOption(void);

/*!
 * \brief affiche le menu en jeu
 * \param[in] pause : true si le jeu est pause, false sinon
 */
void afficheMenuEnjeu(bool pause);

/*!
 * \brief trace un rectangle vide
 * \param[in] xCoin1 : abscisse du premier coin
 * \param[in] yCoin1 : ordonnée du premier coin
 * \param[in] xCoin2 : abscisse du second coin
 * \param[in] yCoin2 : ordonnée du second coin
 * \param[in] taille : epaisseur du trait
 */
void rectangleVide(float xCoin1, float yCoin1, float xCoin2, float yCoin2, float taille);

/*!
 * \brief trace l'indice
 * \param[in] coupJoueur : structure contenant les informations concernant l'indice
 * \param[in] zoom : taille du zoom
 * \param[in] x : abcisse du zoom
 * \param[in] y : ordonnée du zoom
 */
void afficheIndice(coup coupJoueur,int zoom,int x,int y);

/*!
 * \brief affiche l'écran pour changer le nom des joueur
 * \param[in] nomJ1 : nom du joueur 1
 * \param[in] nomJ2 : nom du joueur 2
 * \param[in] joueurActuel : joueur dont le nom est en train d'être modifié
 */
void afficheChangemntNom(char nomJ1[15], char nomJ2[15],int joueurActuel);


/*!
 * \brief change le nom du joueur actuel en fonction du dernier caractère clavier
 * \param[in/out] nomJ1 : nom du joueur 1
 * \param[in/out] nomJ2 : nom du joueur 2
 * \param[in] joueurActuel : joueur dont le nom est en train d'etre modifié
 * \return joueurActuel
 */
int changeNom(char nomJ1[15], char nomJ2[15],int joueurActuel);

/*!
 * \brief affiche les temps restants des joueurs
 * \param[in] joueurActuel
 * le joueur dont ce n'est pas le tour voit son temps restant mis à zero
 */
void afficheTempRestant(int joueurActuel);

/*!
 * \brief affiche le joueur gagnant et son score
 * \param[in] scoreGagnant score du gagnant
 * \param[in] scorePerdant score du perdant
 * \param[in] joueurGagnant nom du joueur gagnant
 * \return rien
 */
void afficheVictoire(int scoreGagnant, int scorePerdant, char joueurGagnant[15]);

#endif
