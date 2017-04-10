/*!
   \file GfxLib.h
   \brief fichier contenant les prototypes des fonctions utiles pour la bibliotheque graphique gfxlib
   \author ghislain.oudinet@yncrea.fr
   \date 16/09/2016

   Partie publique elaboree
   Cette partie est relative a toutes les informations utiles pour
   personnaliser et mieux controler l'environnement graphique de base
*/
// Veuillez reporter tout commentaire a ghislain.oudinet@yncrea.fr


//  Version 3.2 (16/09/2016) : remplacement de demandeAnimation_ips() par un demandeTemporisation() plus générique (qui envoie le message Temporisation)
//		Ajout de la fonction termineBoucleEvenements(), necessaire dorenavant sous FreeGLUT sous Linux pour faire quelques nettoyages avant fin du programme
//		Les actions sur le clavier ne memorisent plus les coordonnees de la souris (a moins de recompiler en activant ACTION_CLAVIER_MEMORISE_POSITION_SOURIS)
//
//	Version 3.1 (19/12/2009) : modification de toucheShiftAppuyee, toucheCtrlAppuyee et toucheAltAppuyee pour qu'elles
//      renvoient l'etat en temps reel, et plus seulement lors du dernier evenement concerne (permet plus de possibilites lors d'animations)
//      homogeneisation de l'ecriture du code du programme principal avec l'equivalence de initialisationGLUT
//      	et initialiationGDI, et utilisation de _main sous Win32 au lieu de main
//		ajout de la fonction messageErreur
//
//	Version 3 (02/11/2009) : simplification de la bibliotheque sous une forme specifique (mais plus limitee, sans 3D) pour compatibilite Windows
//
//	Version 2.6 (12/02/2009) : utilisation d'un GL_QUADS dans la fonction rectangle au lieu de glRectf
//		ajout de la fonction BVR2ARVB
//		ajout de la fonction BVR2ABVR
//		ajout de la fonction creeTexture2D
//		ajout de la fonction rectangleSelonTexture
//		ajout de la fonction libereTexture
//
//	Version 2.5.1 (28/03/2008) : ajout de l'opacite dans le choix de la couleur
//        courante, avec la fonction couleurCouranteOpaque
//
//	Version 2.5 (21/08/2007) : ajout de la gestion des touches speciales du clavier
//		ajout de ecrisImageARVB
//
//	Version 2.4.1 (23/01/07) : ajout de materiauLuminescent
//
//	Version 2.4 (16/01/2007) : ajout de la gestion du message Redimensionnement
//		ajout des fonctions largeurFenetre et hauteurFenetre
//		ajout de modifieFonctionDeplacementPassifSouris et de activeGestionDeplacementPassifSouris
//		ajout de fonctionDeplacementPassifSouris
//		ajout de modePleinEcran et de redimensionneFenetre
//
//	Version 2.3 (23/10/2006) : ajout des fonctions Timer et du redessin programme
//	
//	Version 2.2 (30/06/2006) : prepareFenetreGraphique fait cycler la position
//		de depart des fenetres
//	
//	Version 2.1 : main est sorti de la bibliotheque, pour des besoins pedagogiques,
//		cassant la compatibilite avec les anciens codes. Cependant, on peut reintegrer
//		le main manquant dans chaque programme, a partir du code suivant :
//int main(int argc, char **argv)
//{	initialiseGLUT(argc, argv);
//	gfxMain();
//	return 0;}
//
//	Version 2.0 (29/01/06) : ajout de la gestion de la 3D
//		modification de fonctionRedimensionnement, ajout de sAngleDeVue et sVisualisationMode2D
//		ajout de prepareFenetre_En_DeTaille
//		ajout de passeEnMode3D, passeEnMode2D
//		definitions de Point3DGfx et de Vecteur3DGfx
//		ajout de fixeLuminositeAmbiante, lumiereDiffuse_Couleur_En et placeObservateur
//		ajout de point3D, ligne3D et triangle3D
//		ajout de empileTranslation, empileRotationSelonX, empileRotationSelonY et
//			empileRotationSelonZ
//
//	Version 1.2 : ajout de fonctions d'affichage et de lecture ecran d'images bitmap
//
//	Version 1.1.1 : correction de rafraichitFenetre en rafraichisFenetre
//
//	Version 1.1 : affichage des erreurs OpenGL dans fonctionAffichage
//		afficheImage en cours de developpement

#ifndef GFXLIB_H
#define GFXLIB_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <stdbool.h>
/*#define bool int
#define true (0==0)
#define false (!true)*/



/* Partie publique basique
   Cette partie est relative a toutes les informations utiles pour
   mettre en place simplement un environnement graphique portable */

/*!
 * \brief liste des evementGfxlib
 */
typedef enum {Inactivite, Affichage, Clavier, ClavierSpecial, Souris, BoutonSouris, Initialisation, Redimensionnement, Temporisation}
	EvenementGfx;
/*!
 * \brief liste des état possible des boutons de la souris
 *
 * le scroll genere deux appelle de fonctionBoutonSouris, tmpScroll evite de doublé les scrolls
 */
typedef enum {GaucheAppuye, GaucheRelache, DroiteAppuye, DroiteRelache,ScrollUp,ScrollDown,TmpScroll}
	EtatBoutonSouris;
/*!
 * \brief idk
 */
typedef enum {SuiteDePoints, SuiteDeLignes, SuiteDeTriangles, SuiteDeRectangles, BandeDeTriangles, BandeDeRectangles}
	PrimitiveGfxLib;
/*!
 * \brief liste des touches speciales
 */
typedef enum {ToucheF1 = 1, ToucheF2, ToucheF3, ToucheF4, ToucheF5, ToucheF6, ToucheF7, ToucheF8, ToucheF9, ToucheF10, ToucheF11, ToucheF12,
	ToucheFlecheHaut, ToucheFlecheBas, ToucheFlecheGauche, ToucheFlecheDroite, ToucheNonGeree} TouchesSpeciales;

/*!
 * \brief structure pour manipuler des texture
 */
typedef struct
	{
		int largeur; /*!< Largeur des donnees*/
		int hauteur; /*!< Hauteur des donnees*/
		float proportionX /**< idk*/;
		float proportionY;/**< idk*/
		int *donnees; /*!< Les donnees de la texture*/
		unsigned int numero; /*!< L'identifiant OpenGL de la texture*/
	} Texture2D;


/*!
 * \brief Pour initialiser la partie graphie de la bibliotheque
 * \param argc nombre d'arguments de argv
 * \param argv tableau d'arguments
 */
void initialiseGfx(int argc, char **argv);

/*!
 * \brief prepare une fenetre
 * \param nom nom de la fenetre
 * \param largeur largeur de la fenetre
 * \param hauteur hauteur de la fenetre
 *
 * Prepare une fenetre en specifiant son nom, sa largeur et sa hauteur.
   La fenetre presente un repere orthonorme classique (premier quadrant),
   de largeur pixels sur hauteur pixels
 */
void prepareFenetreGraphique(const char *nom, int largeur, int hauteur);


/*!
 * \brief Lance la boucle de gestion des evenements
 */
void lanceBoucleEvenements(void);
/*!
 * \brief Termine le programme proprement
 */
void termineBoucleEvenements(void);


/*!
 * \brief Fonction de gestion des evenements graphiques, a definir par l'utilisateur
 * \param evenement evement de la gfx à gérer
 */
extern void gestionEvenement(EvenementGfx evenement);



/*!
 * \brief Demande la mise a jour du contenu graphique de la fenetre, en lancant un message d'affichage
 */
void rafraichisFenetre(void);

/*!
 * \brief Efface la fenetre avec la couleur donnee
 * \param rouge composante rouge (entre  0 et 255)
 * \param vert composante vert (entre  0 et 255)
 * \param bleu composante bleu (entre  0 et 255)
 */
void effaceFenetre(int rouge, int vert, int bleu);

/*!
 * \brief Selectionne la couleur courante de dessin
 * \param rouge composante rouge (entre  0 et 255)
 * \param vert composante vert (entre  0 et 255)
 * \param bleu composante bleu (entre  0 et 255)
 */
void couleurCourante(int rouge, int vert, int bleu);

/*!
 * \brief Definit l'epaisseur de trait EN PIXELS DE LA FENETRE servant a afficher les points et les lignes
 * \param epaisseur en pixel
 */
void epaisseurDeTrait(float epaisseur);

/*!
 * \brief Dessine un point de couleur courante aux coordonnees donnees
 * \param x abscisse
 * \param y ordonnée
 */
void point(float x, float y);

/*!
 * \brief  Dessine une ligne de couleur courante aux coordonnees donnees *
 * \param xDepart abscisse de depart
 * \param yDepart ordonné de depart
 * \param xArrivee abscisse d'arrivée
 * \param yArrivee ordonnée d'arrivée
 */
void ligne(float xDepart, float yDepart, float xArrivee, float yArrivee);

/*!
 * \brief Dessine un triangle de couleur courante aux coordonnees donnees
 * \param xCoin1 abscisse coin1
 * \param yCoin1 ordonnée coin 1
 * \param xCoin2 abscisse coin 2
 * \param yCoin2 ordonnée coin 2
 * \param xCoin3 abscisse coin 3
 * \param yCoin3 ordonnée coin 3
 */
void triangle(float xCoin1, float yCoin1, float xCoin2, float yCoin2, float xCoin3, float yCoin3);

/*!
 * \brief Dessine un rectangle de couleur courante aux coordonnees donnees
 * \param xCoin1 abscisse du premier coin
 * \param yCoin1 ordonnée du premier coin
 * \param xCoin2 abscisse du second coin
 * \param yCoin2 ordonnée du second coin
 */
void rectangle(float xCoin1, float yCoin1, float xCoin2, float yCoin2);

/*!
 * \brief Affiche une chaine de caracteres de taille donnee a la position specifiee
 * \param chaine chaine à afficher
 * \param taille taille de la chaine
 * \param x abscisse du point de depart de la chaine
 * \param y ordonnée du point de depart de la chaine
 */
void afficheChaine(const char *chaine, float taille, float x, float y);

/*!
 * \brief Renvoie l'espace occupe par la chaine de caracteres de taille donnee
 * \param chaine taille de la chaine que nous voulons afficher
 * \param taille taille de l'affichage voulu
 * \return
 */
float tailleChaine(const char *chaine, float taille);

/*!
 * \brief Envoie un message Affichage apres la duree specifiee
 * \param millisecondes durée avant l'envoie du nouveau message d'affichage
 */
void demandeRedessinDans_ms(int millisecondes);

/*!
 * \brief Demarre l'envoi periodique de messages Temporisation
 * \param millisecondesEntreAppels nombre de millisecondes entre chaque appel
 */
void demandeTemporisation(int millisecondesEntreAppels);


/*!
 * \brief lis une image
 * \param x
 * \param y
 * \param largeur
 * \param hauteur
 * \param donnees
 *
 * Lis une portion de la fenetre, couvrant largeur*hauteur et demarrant en (x, y)
 * Les donnees lues sont sauvees comme une succession de valeurs B, V, R de type
 * unsigned cha
 */
void lisImage(int x, int y, int largeur, int hauteur, unsigned char *donnees);

/*!
 * \brief ecris un iamge
 * \param x absisse de debut de l'image
 * \param y ordonné du debut de l'imahe
 * \param largeur largeur de l'image
 * \param hauteur hauteur de l'image
 * \param donnees
 */
void ecrisImage(int x, int y, int largeur, int hauteur, const unsigned char *donnees);

#ifndef _WIN32

/*!
 * \brief ecris une image
 * \param x absisse de debut de l'image
 * \param y ordonné du debut de l'imahe
 * \param largeur largeur de l'image
 * \param hauteur hauteur de l'image
 * \param donneesARVB
 *
 * Ecris une image couvrant largeur*hauteur, demarrant en (x, y) et faite de
 * pixels ARVB (stockes dans des int little endian) dans la fenetre
 */
void ecrisImageARVB(int x, int y, int largeur, int hauteur, const int *donneesARVB);

/*!
 * \brief Cree une texture reutilisable de largeur et hauteur donnees, faite de pixels ABVR little endian
 * \param largeur
 * \param hauteur
 * \param pixelsABVR
 * \return
 */
Texture2D *creeTexture2D(int largeur, int hauteur, const int *pixelsABVR);

/*!
 * \brief Permet de modifier les pixels de la texture prealablement definie, en donnant un nouveau tableau de pixels ABVR little endian
 * \param texture
 * \param pixelsABVR
 */
void modifieTexture2D(const Texture2D *texture, const int *pixelsABVR);

/*!
 * \brief Affiche la texture passee en parametre aux coordonnees fournies
 * \param x abscisse
 * \param y ordonnée
 * \param texture texture à afficher
 */
void rectangleSelonTexture(float x, float y, const Texture2D *texture);

/*!
 * \brief Libere les ressources associees a la gestion de la texture
 * \param texture texures à libérers
 */
void libereTexture(Texture2D **texture);
#endif


/*!
 * \brief Renvoie l'abscisse de souris correspondant au dernier evenement Clavier, Souris ou BoutonSouris
 * \return abscisse de la souris
 */
int abscisseSouris(void);

/*!
 * \brief  Renvoie l'ordonnee de souris correspondant au dernier evenement Clavier, Souris ou BoutonSouris
 * \return ordonnee de la souris
 */
int ordonneeSouris(void);

/*!
 * \brief Renvoie le dernier etat de bouton souris traite par l'evenement BoutonSouris
 * \return dernier etat du bouton souris
 */
EtatBoutonSouris etatBoutonSouris(void);

/*!
 * \brief Renvoie le dernier caractere clavier traite par l'evenement Clavier
 * \return le dernier caractère traité par l'evenement clavier
 */
char caractereClavier(void);
/*!
 * \brief renvoie la derniere touche speciale du clavier traitee par l'evenement ClavierSpecial
 * \return la derniere touche speciale du clavier traitee par l'evenement ClavierSpecial
 */
int toucheClavier(void);

/*!
 * \brief Indique l'etat de la touche shift lors du dernier evenement Clavier
 * \return true si la touche shift était appuye lors du dernier appelle d'un evenement
 * \return false si la touche shift n'était pas appuye lors du dernier appelle d'un evenement
 */
bool toucheShiftAppuyee(void);

/*!
 * \brief Indique l'etat de la touche Ctrl lors du dernier evenement Clavier
 * \return true si la touche ctrl était appuye lors du dernier appelle d'un evenement
 * \return false si la touche ctrl n'était pas appuye lors du dernier appelle d'un evenement
 */
bool toucheCtrlAppuyee(void);
/*!
 * \brief Indique l'etat de la touche Alt lors du dernier evenement Clavier
 * \return true si la touche alt était appuye lors du dernier appelle d'un evenement
 * \return false si la touche alt n'était pas appuye lors du dernier appelle d'un evenement
 */
bool toucheAltAppuyee(void);


/*!
 * \brief Renvoie la largeur actuelle de la fenetre
 * \return largeur actuelle de la fenetre
 */
int largeurFenetre(void);

/*!
 * \brief Renvoie la hauteur actuelle de la fenetre
 * \return hauteur actuelle de la fentre
 */
int hauteurFenetre(void);

/*!
 * \brief Demande au systeme de redimensionner la fenetre
 * \param largeur nouvelle largeur demandé
 * \param hauteur nouvelle hauteur demandé
 */
void redimensionneFenetre(int largeur, int hauteur);

/*!
 * \brief Demande au systeme de passer la fenetre en plein ecran
 */
void modePleinEcran(void);



/*!
 * \brief Affiche un message d'erreur de maniere standard pour l'OS
 * \param message message à afficher
 */
void messageDErreur(const char *message);


/*!
 * \brief Active la gestion du deplacement passif de la souris
 */
void activeGestionDeplacementPassifSouris(void);



/* Partie publique elaboree
   Cette partie est relative a toutes les informations utiles pour
   personnaliser et mieux controler l'environnement graphique de base */


#endif
