/*!
   \file outils.c
   \brief fichier contenant les outils utiles dans tous les autres modules
   \author "Billaud William"
   \date "DD"/"Month"/"Year"

	 fichier contenant les fonctions,les structures de données et les enum utiles dans les autres modules
*/

/*!
   \brief enum contenant les couleurs
*/
typedef enum {
	vide /*!< case vide ( niveau 0) */,
	vert /*!< couleur du joueur 1*/,
	rouge /*!< couleur du joueur 2 */,
	neutre /*!< couleur neutre */,
}couleur;

/*!
   \brief structure contenant les pieces

	 Les informations concernant les couleur sont données pour la pièce positionnée en L
*/
typedef struct pieces
{
	couleur c1; /*!< couleur de la case du haut  */
	couleur c2; /*!< couleur de la case du milieu */
	couleur c3; /*!< couleur de la case  a droite*/
	unsigned char numeroPiece; /*!< numero de la pièce */
}pieces;

/*!
   \brief enum contenant les orientations des pièces

	 les orientations sont données vis a vis du joueur regardant l'ecran, une pièces en L est donc en position HD
*/
typedef enum{
	HD /*!< pièce orientée avec un coté vers la haut, et l'autre vers la droite */,
	BD /*!< pièce orientée avec un coté vers le bas, et l'autre vers la droite */,
	BG /*!< pièce orientée avec un coté vers la gauche, et l'autre vers le bas */,
	HG /*!< pièce orientée avec un coté vers la gauche, et l'autre vers le haut */
}orientation;
/*!
   \brief structure contenant des informations concernant un étage d'une case
*/
typedef struct etage{
	unsigned char numeroPiece;/*!< numero de la pièce */
	couleur couleurEtage; /*!< couleur de la pieces sur case */
}etage;

/*!
   \brief structure contenant toutes les couches de la case

	 tabEtage[hauteur] correspond à la pièce visible
*/
typedef struct historiqueCase
{
	unsigned char hauteur; /*!< hauteur de la case (0 si la case est vide) */
	etage tabEtage[20]; /*!< tableau contenant tous les étages de la case */
}historiqueCase;


/*!
   \brief structure contenant les informations pour jouer un coup
*/
typedef struct coup{
	unsigned char numeroPiece;/*!< numero de la pièces à jouer */
	unsigned int xCoup;/*!< abscisse de la case central de la pièces (C2) */
	unsigned int yCoup;/*!< ordonnee de la case central de la pièces (C2) */
	orientation orientationPiece;/*!< orientation de la pièce */
}coup;
