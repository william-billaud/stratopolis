 # Projet Strotapolis

Réalisation du jeu stratopolis en tant que projet étudiant pour l'ISEN Toulon pour l'année universitaire 2016-2017

## Le jeu

#### Généralités
*Stratopolis* :
Dans   ce   jeu   créé   par   _Annick   Lobet_,   chaque   tour   sera   déterminant.   Choisirez-vous
d'agrandir votre territoire, de lui faire prendre de la hauteur ou de contrer l'expansion
adverse ? Les joueurs placent leurs tuiles à tour de rôle afin d'optimiser la présence de
leur couleur. Le score prend en compte la plus grande surface et la plus grande hauteur
de cette surface. Les tuiles s'empilent et un territoire risque d'être divisé à tout moment par
l'adversaire: jusqu'au dernier coup la victoire peut basculer

#### Les règles
- Les règles du jeu sont disponibles dans le programme, à la rubrique **Aide** du menu principal. 
- Lien vers [les règles](https://cloud-toulon.isen.fr/d/0d68030fad/files/?p=/Stratopolis/GIGAMIC_STRATOPOLIS_RULES-FR.pdf&dl=1) du jeu ( en français)
#### Revue de presse
- une [review](https://cloud-toulon.isen.fr/d/0d68030fad/files/?p=/Stratopolis/Stratopolis_Review_-_with_Tom_and_Melody_Vasel.mp4&dl=1) avec Tom et Melody Vasel (en anglais)
- Un [tutoriel](https://cloud-toulon.isen.fr/d/0d68030fad/files/?p=/Stratopolis/Tutorial_-_Stratopolis.mp4&dl=1) (en espagnol)
- Quelques [avis](https://www.trictrac.net/jeu-de-societe/stratopolis)
#### Acheter
Quelques liens pour acheter le jeu
- [gigamic](http://www.gigamic.com/jeu/stratopolis)
- [ludifolie](http://www.ludifolie.com/produit.php?ref=stratopolis)
- [variantes](http://www.variantesi.com/jeu-strategie-tactique-moderne-boutique/40645-Stratopolis-3420000000000.html)
- [amazon](https://www.amazon.fr/dp/B0079XFP7E)
- [fnac](http://www.fnac.com/Gigamic-Stratopolis/a4792732/w-4)

## Utilisation
##### Pré-requis
- un ordinateur avec un système linux 
- bibliothèque LX11 
- [OpenGL](https://www.opengl.org/)/[GLUT](https://www.opengl.org/resources/libraries/glut/) 
- [GCC](https://gcc.gnu.org/) (une version récente est conseillée >5.0) 
- [make](https://www.gnu.org/software/make/)
##### Compilation
la compilation s'effectue à l'aide de la commande

```bash
make
```
 dans le dossier racine du projet.

##### Lancement
Le programme se lance grâce à la commande

```bash
./main
```
 dans le dossier racine du projet
##### Nettoyage
La commande

```bash
make clean && make
```
permet la regénération de l'ensemble des binaires
##### Commandes
- La souris est utilisée pour cliquer sur n'importe quel bouton (menus, ou en jeu)
- Pour changer les noms de joueurs il faut cliquer sur le bouton changer les noms dans le menu des option, la touche retour permet de supprimer un caractère, et la touche entrée permet de valider et de passer au nom suivant, une fois le deuxième nom rentré, la touche entrée permet de retourner au menu des options. 
- En jeu, pour jouer une pièce il faut la sélectionner, les flèches ainsi que la molette de la souris permettent de la faire tourner. 
- L'utilisation de la molette de la souris en étant appuyé sur la touche ctrl permet de zoomer ou dezoomer la grille. 
- La touche Z permet de trouver le zoom optimal pour la grille. 
- La touche F permet de rentrer/sortir du mode pleine écran. 
- La touche Q permet de quitter le jeu. 
##### Notice
-Le programme peut être redimensionné à tout moment, il reste fonctionnel pour une résolution supérieure à 400px par 400px, en dessous il devient difficile de jouer convenablement. 
- Au lancement du programme, un menu principal vous propose les options suivantes (la sélection se fait à la souris) :
* **Jouer** : Commencer à jouer avec les paramètres sélectionnés.
* **Options** : Choisir les options parmi les possibilités suivantes :
  * *Mode de jeu* : Le mode Joueur VS Joueur permet de défier un ami à jouer à deux sur cet ordinateur à tour de rôle, Joueur VS IA permet de faire une partie contre l'ordinateur.
  * *Difficulté IA* : En mode Joueur VS IA, permet de choisir parmi 5 niveaux de difficulté pour l'ordinateur. (Attention : Le temps de réponse de l'ordinateur augmente au plus la difficulté est élevée)
  * *Limite de temps* : En mode Joueur VS Joueur, permet de fixer une limite de temps pour chaque tour. Lorsque cette limite est dépassée la pièce du joueur trop lent est placée aléatoirement sur le plateau, dans le respect des règles de placement de tuile.
  * *Changer noms* : Permet de modifier les noms qui seront affichés en cors de partie, pour plus de convivialité.
  * *Retour* : Valider et revenir au menu principal.
* **Aide** : Permet de consulter un résumé des règles de jeu, cliquez n'importe où pour revenir au menu principal.
* **Quitter** : Permet de quitter le programme.

- En jeu, deux barres latérales affichent les informations relatives à chacun des joueurs, à savoir son nom, son score, le nombre de tuiles dont il dispose, le temps écoulé depuis le début de son tour ainsi que la tuile qu'il peut placer pendant son tour. 
- Le joueur dont c'est le tour a son interface en surbrillance, tandis que l'autre joueur est grisé. 
Le joueur dont c'est le tour peut cliquer sur sa pièce pour la sélectionner (elle suivra alors le curseur de la souris), la faire tourner avec la molette de la souris ou les flèches du clavier et la placer (Si la pièce ne peut pas être posée, alors elle est affichée grisée). La hauteur des pièces posées sur le plateau est visible par le chiffre affiche dessus, *1* correspondant au niveau d'une pièce posée à même le sol. 
- Le joueur peut zoomer ou dézoomer sur le plateau à tout moment en maintenant la touche Ctrl et la molette de la souris. Il peut également appuyer sur la touche *Z* pour obtenir automatiquement le meilleur zoom. 
- Trois boutons en bas à gauche permettent de mettre le jeu en pause (cliquer à nouveau sur le bouton pour continuer), quitter le jeu et revenir au menu principal (la partie ne sera pas sauvegardée) et obtenir un indice sur le meilleur coup à jouer ce tour (Le coup sera affiché sur le plateau par une pièce clignotante) 
- A la fin de la partie, le joueur gagnant est affiché ainsi que les scores de chaque joueur. Vous pouvez cliquer pour revenir au menu principal.
##### Divers
- L'IA joue dans un temps court (inférieur à 30secondes) uniquement pour les niveaux de difficulté facile et moyen, la recherche de coup pour les difficultés supérieures peut se réveler extrèmement longue (supérieure à 10 minutes) 
-L'utilisation de valgrind peut provoquer des lenteurs au niveau du thread parrallèle lancé pour l'IA, ce qui nuit à la fluidité du jeu 
- Deux fuites mémoires ont été reperées, mais elle semblent être
causées par la librairie libisentlib. Mais la mémoire perdue reste la même quelle que soit la durée du programme (la fuite n'a donc pas lieu sur la durée)
## Auteurs
- [*HIPAULT Theo (chef de projet)*](https://github.com/Parazar)
- [BILLAUD William](https://github.com/william-billaud)

## Remerciement
[M. Colonna](http://fm.colonna.free.fr/?Accueil), Docteur en informatique - Enseignant-chercheur à l'ISEN Toulon
