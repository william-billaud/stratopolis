/*!
* \file moteur.c
* \brief fichier contenant les fonction utils au moteur du jeu
* \author billaud
* \author hipault
* \date 22/01/17
*/

#include "moteur.h"

extern PLATEAU plat;/**<\var variable global contenant le plateau*/

extern ORDREPIECE ordreJoueurs[2];/**<\var tableau contenant l'ordre des pièces des joueurs*/

/*!
 * \brief initialise le plateau (pose la pièce initiale)
 * \return 0 si tout s'est bien passé
 * \return -1 si un problème a eu lieu
	*/
int initPlateau(void)
{
	int i_x;
    /**< index des abscisse*/
	int i_y;
    /**< index des ordonnées*/

	for (i_x = 0; i_x < TAILLEMAX; ++i_x) {
		for (i_y = 0; i_y < TAILLEMAX; ++i_y) {
			setCaseAZero(&(plat[i_x][i_y]));
			plat[i_x][i_y].x = i_x;
			plat[i_x][i_y].y = i_y;
		}
	}
	//pose la pièce de depart (pièce numero 0)
	plat[80][80].hauteur = 1;
	plat[80][80].tabEtage[1].couleurEtage = vert;
	plat[80][80].tabEtage[1].numeroPiece = 0;
	plat[81][80].hauteur = 1;
	plat[81][80].tabEtage[1].couleurEtage = rouge;
	plat[81][80].tabEtage[1].numeroPiece = 0;
	return 0;
}

/*!
 * \brief choisis le joueur qui commence
 * \return 1 si le joueur 1 commence
 * \return 2 si le joueur 2 commence
	*/
int choisisJoueur(void)
{
	/* recupère le timestamp actuel et le stocke dans a) */
	unsigned int a = (unsigned int)time(NULL);
    /**<\var seed recupere à partir du timestamp*/
	//definit la seed du lancer aléatoire
	srand(a);
	//effectue le lancer aléatoire et reduit les possibilité à 1 ou 2
	return rand() % 2;
}

/*!
 * \brief initialise l'ordre des pièces dans un tableau
 * \param joueur numero du joueur
 * \return 0 si la fonctions n'a pas eu de problème pour s'effectuer
 * \return -1 si il y a eu une erreur
	*/
int initOrdrePieces(int joueur)
{
	int i;
	unsigned int a;
    /**<\var seed pour le rand()*/
	int n;
    /**< nombre de pièces à tirer restantes*/
	int r;
    /**< resultat du tirage aléatoire*/
	if (joueur != 1 && joueur != 2) {
		return -1;
	}
	int liste[20];
	for (i = 0; i < 20; ++i) {
		liste[i] = i + 1;
	}
	/* recupère le timestamp actuel et le stocke dans a) */
	a = (unsigned int)time(NULL);
    /**< seed récupère à partir du timestamp*/
	//definit la seed du lancer aléatoire
	srand(a + 100 * joueur);
	for (i = 0; i < 19; ++i) {
		n = 20 - i - 1;
		//tirage d'une valeur aléatoire comprise entre 0 et n (nombre de pièces à tirer restante
		r = rand() % (n);
		//la pièce tirée est ajoutée à la liste
		ordreJoueurs[joueur - 1][i] = liste[r] + 20 * (joueur - 1);
		//sa place dans la liste est remplacée par la celle la plus en haut du tableau
		liste[r] = liste[n];
	}
	// on ajoute le dernier terme
	ordreJoueurs[joueur - 1][19] = liste[0] + 20 * (joueur - 1);
	// on ajoute le nombre de pièces disponibles dans la dernière case
	ordreJoueurs[joueur - 1][20] = 0;
	return 0;
}

/*!
 * \brief recherche si la case possède une tuile adjacente
 * \param x : ordonnee de la case
 * \param y : abscisse de la case
 * \return true si la case possede une tuile adjacente
 * \return false si la case ne possède pas de tuile adjacente
	*/
bool possedeTuileAdjacente(int x, int y)
{
	historiqueCase *tab[4];
	int i;
	tab[0] = getCase(x - 1, y);
	tab[1] = getCase(x + 1, y);
	tab[2] = getCase(x, y + 1);
	tab[3] = getCase(x, y - 1);
	for (i = 0; i < 4; ++i) {
		if (getHauteurCase(tab[i]) > 0) {
			return true;
		}
	}
	return false;
}

/*!
 * \brief permet de savoir si une superposition de couleur est valide
 * \param haut : pièce du haut
 * \param bas : pièce du bas
 * \return true si la superposition est valide
 * \return false si la superpostion est invalide
	*/
bool estValideSuperposition(couleur haut, couleur bas)
{
	if ((haut == rouge && bas == vert) || (haut == vert && bas == rouge)) {
		return false;
	} else {
		return true;
	}
}

/*!
 * \brief verifie qu'un coup est valide
 * \param[in] coupJoueur : coup du joueur
 * \return true si le coup est valide
 * \return false si le coup n'est pas possible
	*/
bool estValideCoup(coup coupJoueur)
{
	historiqueCase *c1, *c2, *c3;
	int x1, x3, y1, y3;
	historiqueCase *caseCoups[3];
	if (getCasesFromCoup(coupJoueur, caseCoups) == -1) {
		return false;
	}
	c1 = caseCoups[0];
	c2 = caseCoups[1];
	c3 = caseCoups[2];
	x1 = caseCoups[0]->x;
	x3 = caseCoups[2]->x;
	y3 = caseCoups[2]->y;
	y1 = caseCoups[0]->y;
	//verifie que toutes les cases en dessous sont à la même hauteur
	if (getHauteurCase(c1) != getHauteurCase(c2)
	    || getHauteurCase(c1) != getHauteurCase(c3)) {
		return false;
	}
	//si la pièce va être posée au niveau zero, verifie que l'une des tuiles possède un coté adjacent à une autre tuile
	if (getHauteurCase(c1) == 0) {
		if (possedeTuileAdjacente(x1, y1) == false
		    && possedeTuileAdjacente(x3, y3) == false
		    && false == possedeTuileAdjacente(coupJoueur.xCoup,
						      coupJoueur.yCoup)) {
			return false;
		}
	} else {
		//sinon verifie que toutes les superpositions sont valides
		if (!estValideSuperposition
		    (couleurPiece(coupJoueur.numeroPiece, 1),
		     (couleur) getCouleurCase(c1))
		    ||
		    !estValideSuperposition(couleurPiece
					    (coupJoueur.numeroPiece, 2),
					    (couleur) getCouleurCase(c2))
		    ||
		    !estValideSuperposition(couleurPiece
					    (coupJoueur.numeroPiece, 3),
					    (couleur) getCouleurCase(c3))) {
			return false;
		}
		//verifie que la pièce va être posée sur au moins deux autres pièces
		if (getNumeroPiece(c1) == getNumeroPiece(c2)
		    && getNumeroPiece(c1) == getNumeroPiece(c3)) {
			return false;
		}
	}
	return true;
}

/*!
 * \brief pose une tuile sur le plateau
 * \param[in] coupJoueur : coup du joueur
 * \return 1 si le coup a pu être effectué
 * \return 0 si le coup est invalide
 * \return -1 en cas d'erreur
	*/
int joueCoup(coup coupJoueur)
{

	if (estValideCoup(coupJoueur) == false) {
		return 0;
	}
	historiqueCase *caseCoups[3];
	if (getCasesFromCoup(coupJoueur, caseCoups) == -1) {
		return -1;
	}

	int i;
	for (i = 0; i < 3; ++i) {
		//change la hauteur des cases
		caseCoups[i]->hauteur += 1;
		//ajoute le numero de pièce a cette hauteur
		caseCoups[i]->
		    tabEtage[getHauteurCase((caseCoups[i]))].numeroPiece =
		    coupJoueur.numeroPiece;
	}
	//modifie les couleurs des cases
	caseCoups[0]->tabEtage[getHauteurCase((caseCoups[0]))].couleurEtage =
	    PIECE[coupJoueur.numeroPiece].c1;
	caseCoups[1]->tabEtage[getHauteurCase((caseCoups[1]))].couleurEtage =
	    PIECE[coupJoueur.numeroPiece].c2;
	caseCoups[2]->tabEtage[getHauteurCase((caseCoups[2]))].couleurEtage =
	    PIECE[coupJoueur.numeroPiece].c3;

	return 1;
}

/*!
 * \brief dejoue un coup
 * \param[in] coupAnnule : coup à annuler
 * \return 1 si tout s'est bien passé
 * \return -1 si le coup n'as pas pu être annulé
	*/
int dejoueCoup(coup coupAnnulle)
{
	historiqueCase *caseCoups[3];
	if (getCasesFromCoup(coupAnnulle, caseCoups) == -1) {
		return -1;
	}
	int i;
	//on verifie que rien n'a été posé sur la pièce
	for (i = 0; i < 3; ++i) {
		if ((int)coupAnnulle.numeroPiece !=
		    getNumeroPiece((caseCoups[i]))) {
			return -2;
		}
	}
	for (i = 0; i < 3; ++i) {
		caseCoups[i]->
		    tabEtage[getHauteurCase((caseCoups[i]))].couleurEtage =
		    vide;
		caseCoups[i]->
		    tabEtage[getHauteurCase((caseCoups[i]))].numeroPiece = 41;
		caseCoups[i]->hauteur -= 1;
	}
	return 1;

}

/*!
 * \brief calcule le score d'un joueur
 * \param[in] joueur : numero du joueur
 * \return score du joueur
 * \return -1 en cas d'erreur
	*/
int calculScore(int joueur)
{
	int score = 0;
	int scoreTmp;
	int i;
	int j;
	int match = 0
    /**<\var 0 si ni la case a gauche ou en dessous est de la meme couleur, 1 si l'une des deux, 2 si les deux le sont*/
	    ;
	couleur couleurJoueur;
	couleur couleurCase;
	listeBlock *liste = NULL;
	listeBlock *tmp = NULL;
	listeBlock *tmpB = NULL;
	caseCalcul *listeCase = NULL;
	if (joueur == 0) {
		couleurJoueur = rouge;
	} else if (joueur == 1) {
		couleurJoueur = vert;
	} else {
		return -1;
	}
	for (i = 0; i < TAILLEMAX; ++i) {
		for (j = 0; j < TAILLEMAX; ++j) {
			couleurCase = (couleur) getCouleurCase(getCase(i, j));
			//si la case n'est pas de la couleur du joueur on passe à la prochaine iteration
			if (couleurCase != couleurJoueur) {
				continue;
			}
			match = 0;
			//si la case à droite est de la meme couleur
			if (getCouleurCase(getCase(i - 1, j)) == (int)
			    couleurJoueur) {
				listeCase = NULL;
				tmp = liste;
				//on cherche dans quel bloc cette case est
				while (listeCase == NULL && tmp != NULL) {
					if (estDansBlock
					    (i - 1, j, tmp->debutBlock)) {
						listeCase = tmp->debutBlock;
					} else {
						tmp = tmp->next;
					}
				}
				if (tmp != NULL) {
					//si on l'a trouvé on ajoute la case actuelle au block de la case à droite
					tmp->debutBlock =
					    ajouteCaseCalcul(tmp->debutBlock, i,
							     j,
							     getHauteurCase
							     (getCase(i, j)));
					match = 1;
				} else {
					printf("I : %d J :%d \n",i,j);
					puts("erreur dans la calcul du score A");
				}

			}
			//si la case en dessous est de la meme couleur
			if (getCouleurCase(getCase(i, j - 1)) ==
			    (int)couleurJoueur) {
				//et si la case à droite n'était pas de la même couleur
				if (match == 0) {
					//on fait pareil que dans le cas ou la case à droite était de la meme couleur
					listeCase = NULL;
					tmp = liste;
					while (listeCase == NULL && tmp != NULL) {
						if (estDansBlock
						    (i, j - 1,
						     tmp->debutBlock)) {
							listeCase =
							    tmp->debutBlock;
						} else {
							tmp = tmp->next;
						}
					}
					if (tmp != NULL) {
						tmp->debutBlock =
						    ajouteCaseCalcul
						    (tmp->debutBlock, i, j,
						     getHauteurCase(getCase
								    (i, j)));
						match = 1;
					} else {
						puts("erreur dans la calcul du score B");
					}
				} else {
					//si la case à droite et celle du dessous sont de la bonne couleur
					//on verifie si elle sont dans le meme bloc
					//si elle sont dans le meme bloc, il n'y a rien à faire
					if (!estDansBlock
					    (i, j - 1, tmp->debutBlock)) {
						tmpB = liste;
						listeCase = NULL;
						//si elle sont dans des blocs differents, on cherche le block de la case du dessous
						while (listeCase == NULL
						       && tmpB != NULL) {
							if (estDansBlock
							    (i, j - 1,
							     tmpB->debutBlock))
							{
								listeCase =
								    tmpB->debutBlock;
							} else {
								tmpB =
								    tmpB->next;
							}
						}
						//et on concatene les deux
						if (tmpB != NULL) {
							concateneCaseCalcul
							    (liste,
							     tmp->debutBlock,
							     tmpB->debutBlock);
						} else {
							puts("erreur dans calcul score C");
						}
					}
				}
				match += 1;
			}
			if (match == 0) {
				// si aucun des deux, on crée un nouvelle liste
				tmp = malloc(sizeof *tmp);
				tmp->next = liste;
				tmp->debutBlock =
				    ajouteCaseCalcul(NULL, i, j,
						     getHauteurCase(getCase
								    (i, j)));
				liste = tmp;
				tmp = NULL;
			}
		}
	}
	//on calcule le score de chaque liste et on trouve le plus grand

	//on libère chaque liste et on trouve celle avec le score le plus grand
	while (liste != NULL) {
		scoreTmp = scoreListe(liste->debutBlock);
		score = (scoreTmp > score) ? scoreTmp : score;
		libereCaseCalcul(liste->debutBlock);
		tmp = liste;
		liste = liste->next;
		free(tmp);
	}
	return score;
}

/*!
 * \brief fonction permettant de savoir si un couple de coordonées est present dans une liste simplement chainée
 * \param x : abscisse à tester
 * \param y : ordonnée à tester
 * \param caseDebut : tête de la liste
 * \return true si le couple est présent dans la liste
 * \return false si le couple n'est pas présent dans la liste
	*/
bool estDansBlock(int x, int y, caseCalcul * caseDebut)
{
	caseCalcul *caseTeste;
	caseTeste = caseDebut;
	while (caseTeste != NULL) {
		if (caseTeste->x == x && caseTeste->y == y) {
			return true;
		}
		caseTeste = caseTeste->next;
	}
	return false;
}

/*!
 * \brief ajoute une caseCalcul en debut de ligne et initialise ses valeurs
 * \param tete : pointeur de le tête precedente
 * \param x : abscisse de la case
 * \param y : ordonnée de la case
 * \param hauteur : hauteur de la case
 * \return pointeur vers la nouvelle tete
	*/
caseCalcul *ajouteCaseCalcul(caseCalcul * tete, int x, int y, int hauteur)
{
	caseCalcul *ptr = malloc(sizeof *ptr);
	ptr->next = tete;
	ptr->y = y;
	ptr->x = x;
	ptr->hauteur = hauteur;
	return ptr;
}

/*!
 * \brief fonction libérant une liste de caseCalcul
 * \param tete : tête de la liste à libérer
	*/
void libereCaseCalcul(caseCalcul * tete)
{
	caseCalcul *tmp;
	while (tete != NULL) {
		tmp = tete->next;
		free(tete);
		tete = tmp;
	}
}

/*!
 * \brief calcule le score donné par une liste
 * \param tete : tête de la liste
 * \return score de la liste
	*/
int scoreListe(caseCalcul * tete)
{
	caseCalcul *tmp;
	tmp = tete;
	int hauteur = 0;
	int etendu = 0;
	while (tmp != NULL) {
		//si la hauteur est plus grande que la maximum precedente on la remplace
		hauteur = (tmp->hauteur > hauteur) ? tmp->hauteur : hauteur;
		tmp = tmp->next;
		etendu += 1;
	}
	return etendu * hauteur;
}

/*!
 * \brief concatène deux listes de caseCalcul dans listeBlock et libère la case ainsi libérée
 * \param block : listeBlock dans laquelle il faut concatener les liste de caseCalcul
 * \param listeA
 * \param listeB : liste à ajouter a la fin de listeA
	*/
void concateneCaseCalcul(listeBlock * block, caseCalcul * listeA,
			 caseCalcul * listeB)
{
	listeBlock *tmp;
	//on parcours la listeA jusqu'au bout
	while (listeA->next != NULL) {
		listeA = listeA->next;
	}
	//on y ajoute la liste B
	listeA->next = listeB;
	//on parcours la liste de block à la recherche du debut de la listeB
	//traitement special si listeB correspond au tout premier block
	if (block->debutBlock == listeB) {
		block->debutBlock = block->next->debutBlock;
		tmp = block->next;
		block->next = block->next->next;
	} else {
		while (block->next->debutBlock != listeB) {
			block = block->next;
		}
		tmp = block->next;
		block->next = tmp->next;
	}
	free(tmp);
}

/*!
 * \brief
 * \param joueur : pointeur vers un entier contenant le joueur qui commencera
 * \return -1 si l'initation des pièce du joueur 1 a eu un problème
 * \return -2 si l'initiation des pièces du joueur 2 a eu un problème
 * \return -4 si le plateau a été mal initialisé
 * \return somme des retour precedents ( à la manière du chmod)
	*/
int initPartie(int *joueur)
{
	int retour = 0;
	retour += initPiece();
	retour += initOrdrePieces(1);
	retour += 2 * initOrdrePieces(2);
	retour += 4 * initPlateau();
	*joueur = choisisJoueur();
    gestionDuree(0);
	gestionDuree(2);
	gestionDuree(4);
	return retour;
}

/*!
 * \brief trouve un coup aleatoire pour le joueur
 * \param joueur
 * \return un coup aleatoire valide
	*/
coup coupAleatoire(int joueur)
{
	coup cp;
	orientation or[4] = {HD, HG, BD, BG};
	unsigned int i;
	unsigned int j;
	unsigned int i_r,j_r;
	int i_o;
	//variables necessaires pour reduire le nombre de possibilités à tester
	unsigned int zoom;
	unsigned int l;
	unsigned int h;
	cp.numeroPiece = 42;
	cp.yCoup = 0;
	cp.xCoup = 0;
	cp.orientationPiece = HD;
	//on reduit le champ des possibiltés
	if (trouveMeilleurZoom(&l, &h, &zoom) == -1) {
		return cp;
	}
	cp.numeroPiece = (unsigned int) ordreJoueurs[joueur][ordreJoueurs[joueur][20]];
	srand((unsigned int) time(NULL));
	i_r= (unsigned int) (rand() % TAILLEMAX);
	j_r= (unsigned int) (rand() % TAILLEMAX);
	for (i = l; i < l + zoom; ++i) {
		for (j = h; j < h + zoom; ++j) {
			for (i_o = 0; i_o < 4; ++i_o) {
				cp.orientationPiece = or[i_o];
				cp.xCoup =l+(i+i_r)%zoom;
				cp.yCoup = j+(j+j_r)%zoom;
				if(estValideCoup(cp))
				{
					return cp;
				}
			}
		}
	}
	return cp;
}
