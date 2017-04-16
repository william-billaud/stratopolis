/* Veuillez reporter tout commentaire a  */
/*!
 * \file BmpLib.h
 * \brief entete necessaire pour la manipulation d'image
 * \author ghislain.oudinet@isen.fr
 *
 * Partie publique elaboree
 * Cette partie est relative a toutes les informations utiles pour
 * personnaliser et mieux controler l'interaction avec les fichiers BMP
 */

#ifndef BMPLIB_H
#define BMPLIB_H

#include <stdbool.h>


/*!
 * \brief structure contenant les donnée d'une image RGV
 */
typedef struct
{
	int largeurImage /*!< largeur de l'image */;
	int hauteurImage /*!< hauteur de l'image */;
	unsigned char *donneesRGB; /*!< Donnees sauvees dans l'ordre bleu-vert-rouge */
} DonneesImageRGB;


/*!
 * \brief[in] Fonction s'occupant de la liberation complete d'une structure DonneesImageRGB
 * \param structure
 */
void libereDonneesImageRGB(DonneesImageRGB **structure);

/*!
 * \brief  Fonction essayant de lire le fichier passé en parametre
 * \param nom
 * \return une structure
	contenant les informations de l'image en cas de succes, NULL sino
 */
DonneesImageRGB *lisBMPRGB(char *nom);

/*!
 * \brief Fonction ecrivant les informations de l'image dans le fichier passe en parametre
 * \param donneesImage
 * \param nom
 * \return faux en cas de probleme, vrai sinon
 */
bool ecrisBMPRGB_Dans(DonneesImageRGB *donneesImage, char *nom);

#endif
