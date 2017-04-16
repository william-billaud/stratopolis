 # Projet Strotapolis

Réalisation du jeu stratopolis en tant que projet étudiant pour l'ISEN Toulon pour l'année universitaire 2016-2017

## Le jeu 

####généralités
*Stratopolis* :
Dans   ce   jeu   créé   par   _Annick   Lobet_,   chaque   tour   sera   déterminant.   Choisirez-vous
d'
agrandir
 votre territoire, de lui faire 
prendre de la hauteur
 ou de 
contrer l'expansion
adverse ? Les joueurs placent leurs tuiles à tour de rôle afin d'
optimiser la présence de
leur couleur
. Le score prend en compte la plus grande surface et la plus grande hauteur
de cette surface. Les tuiles s'empilent et un territoire risque d'être divisé à tout moment par
l'adversaire: jusqu'au dernier coup la victoire peut basculer

####les règles
lien vers [les règles](https://cloud-toulon.isen.fr/d/0d68030fad/files/?p=/Stratopolis/GIGAMIC_STRATOPOLIS_RULES-FR.pdf&dl=1) du jeu ( en français)
####revue de presse
une [review](https://cloud-toulon.isen.fr/d/0d68030fad/files/?p=/Stratopolis/Stratopolis_Review_-_with_Tom_and_Melody_Vasel.mp4&dl=1) avec Tom et Melody Vasel (en anglais)\
un [tutoriel](https://cloud-toulon.isen.fr/d/0d68030fad/files/?p=/Stratopolis/Tutorial_-_Stratopolis.mp4&dl=1) (en espagnol)\
Quelques [avis](https://www.trictrac.net/jeu-de-societe/stratopolis) 
####acheter
Quelques liens pour acheter le jeu
- [gigamic](http://www.gigamic.com/jeu/stratopolis)
- [ludifolie](http://www.ludifolie.com/produit.php?ref=stratopolis)
- [variantes](http://www.variantesi.com/jeu-strategie-tactique-moderne-boutique/40645-Stratopolis-3420000000000.html)
- [amazon](https://www.amazon.fr/dp/B0079XFP7E)
-  [fnac](http://www.fnac.com/Gigamic-Stratopolis/a4792732/w-4)

## Utilisation
#####pré-requis
-un ordinateur avec un système linux\
-bibliothèque LX11\
-[OpenGL](https://www.opengl.org/)/[GLUT](https://www.opengl.org/resources/libraries/glut/)\
-[GCC](https://gcc.gnu.org/) (une version recente est conseillé >5.0)\
-[make](https://www.gnu.org/software/make/)
#####compilation
la compilation s'effectue à l'aide de la commande 

```bash 
make
```
 dans le dossier racine du projet.

#####lancement
le programme ce lance grâce a la commande 
 
```bash 
./main 
```
 dans le dossier racine du projet
#####nettoyage
la commande 

```bash
make clean && make
```
permet la regeneration de l'ensemble des binaires 
##### commandes
-la souris peut êtres utilisée pour cliquer sur n'importe quelle bouton\
-pour changer les noms de joueurs il faut cliquer sur le bouton changer les noms dans le menu des option, la touche retour permet de supprimer un caractère, et la touche entrée permet de valider et de passer au nom suivants, une fois le deuxième nom rentrée, la touche entrée permet de retourner au menu des options.\
-pour jouer une pièce il faut la selectionner, les flèches ainsi que la molette de la souris permettent de la faire tourner.\
-l'utilisation de la molette de la souris en étant appuyé sur la touche ctrl permet de zoomer ou dezoomer la grille.\
-la touche Z permet de trouver le zoom optimal pour la grille.\
-la touche F permet de rentrer/sortir du mode pleine écran.\
-la touche Q permet de quitter le jeu.\
#####divers
-L'ia joue dans un temp court (<30secondes) uniquement pour les niveaux de difficulté facile et moyen, la recherche de coup pour les difficultées superieurs peut se réveler extrement longue (>10 minutes)\
-L'utilisation de valgrind peut provoquer des lenteurs au niveau du thread parrallèle lancé pour l'ia, ce qui nuit à la fluidité du jeu\
-Deux fuites mémoires ont été reperées, mais elle semblent êtres causée par la librairie libisentlib. Mais la memoire perdu reste la même quelques soit la durée du programme (la fuite n'a donc pas lieu sur la durée)
## Auteurs
- [*HIPAULT Theo (chef de projet)*](https://github.com/Parazar)
- [BILLAUD William](https://github.com/william-billaud)

##Remerciement
[M. Colonna](http://fm.colonna.free.fr/?Accueil), Docteur en informatique - Enseignant-chercheur à l'ISEN Toulon