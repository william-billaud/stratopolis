/*!
* \file affichage.c
* \brief fichier contenant les fonctions d'affichages
* \author billaud et hipault
* \date 22/01/17
*/

#include "affichage.h"


void cercle(float centreX, float centreY, float rayon)
{
    const int Pas = 20; // Nombre de secteurs pour tracer le cercle
    const double PasAngulaire = 2.*M_PI/Pas;
    int index;

    for (index = 0; index < Pas; ++index) // Pour chaque secteur
    {
        const double angle = 2.*M_PI*index/Pas; // on calcule l'angle de depart du secteur
        triangle(centreX, centreY,(float) (
                 centreX+rayon*cos(angle)), (float) (centreY+rayon*sin(angle)),
                 (float)(centreX+rayon*cos(angle+PasAngulaire)),(float)(centreY+rayon*sin(angle+PasAngulaire)));
        // On trace le secteur a l'aide d'un triangle => approximation d'un cercle
    }
}
