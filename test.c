/**
* \file test.c
* \brief fichier de test
* \author billaud.william
*
* \details permet d'effectuer les tests unitaires	
*/

int testVar;/**< test description*/

/**
* \brief structure des test 
*/
typedef struct {
	
	int a;/**< a est un entier */ 
}teststruct;


/** 
*	\brief variable b qui ne sert a rien
*/
int b;

/**
* \brief fonction de test
* \param int a entier 1
* \param int c entier 2
* \return taille max
* \details description plus precise de la fonction
*/
int testfonction(int a,int c);

/**
*\brief description breve de l'enumeration
*\details un peu plus de details 
*etc
*etc
*/
typedef enum{
valeur1/**<description valeur 1*/,
valeur2/**<description valeur 2*/,

} enum1;
