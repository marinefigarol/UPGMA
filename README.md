# UPGMA

Ce programme permet la construction d'un arbre phylogénétique basé sur la méthode UPGMA, à partir d'une matrice de distance. Il affiche la matrice  de distance initiale, puis la matrice modifiée ainsi que les racines  associées à l'arbre en construction à partir de cette matrice au fur et  à mesure. A la fin, l'arbre phylogénétique sous forme d'une liste parenthésée  reflétant les relations de parenté est affiché.

## Informations

Ce programme est un projet réalisé dans le cadre de ma première année de master de bioinformatique. Le but était de nous faire manipuler les pointeurs, et d'éviter les fuites mémoire.

Afin de vérifier qu'iln'y a aucune fuite mémoire, <code>valgrind</code> a été utilisé. Pour cela, il suffit de lancer la commande suivante :

<pre>
<code>valgrind --track-origins=yes --leak-check=full ./main</code>
</pre>

## Exécuter ce programme

Vous avez besoin de <code>gcc</code> et <code>make</code> pour pouvoir lancer le programme.

Une fois les fichiers téléchargés, placez-vous dans le dossier et compilez le code source :<br>

<pre>
<code>cd UPGMA
make</code>
</pre>

Vous pouvez désormais lancer le programme en faisant :

<pre>
<code>./main</code>
</pre>


## Algorithme UPGMA

On veut créer un arbre phylogénétique schématisant les liens de parentés de n gènes homologues *g<sub>0</sub>*, ..., *g<sub>n-1</sub>*. Pour cela, on dispose au préalable d'une matrice de distance *M* entre ces *n* gènes. *M* est au départ une matrice carrée de taille *n*. Chaque cellule *M[i][j]* de *M* contient un nombre décimal qui corespond à la distance entre les *g<sub>i</sub>* et *g<sub>j</sub>* (*M* est donc symétrique avec sa diagonale nulle).

### 1.1 L'idée

On construit l'arbre phylogénétique de façon itérative :
  - Au départ, les feuilles de l'arbre sont les *n* gènes.
  - A chaque étape de l'algorithme, on regroupe les deux gènes (ou groupes de gènes) *g<sub>i</sub>* et *g<sub>j</sub>* les plus proches afin de former un nouveau groupe de gènes. Le nouveau groupe est représenté comme un noeud de l'arbre dont les fils sont *g<sub>i</sub>* et *g<sub>j</sub>*.
  - On itère ce processus jusqu'à ce qu'il ne reste plus que deux groupes de gènes. On les rassemble pour former la racine de l'arbre.
  
  ### 1.2 L'algorithme
  
  A chaque itération, la matrice de distance *M* contient l'ensemble des distances entre les noeuds de l'arbre qu'on a déjà construits. Les pointeurs vers les noeuds de l'arbre qu'on a déjà construits sont stockés dans une liste chaînée *racines*. Au départ, la liste *racines* devra contenir les pointeurs vers les noeuds (feuilles) *noeud<sub>0</sub>*, ..., *noeud<sub>n-1</sub>* correspondant aux gènes *g<sub>0</sub>*, ..., *g<sub>n-1</sub>*.<br>
  A tout moment, la *i<sup>ème</sup>* ligne (respectivement colonne) de *M* contient les distances du noeud pointé par le *i<sup>ème</sup>* maillon de la liste *racines* à l'ensemble des noeuds pointés par tous les maillons de la liste *racines*.<br>
  A chaque itération *k*, on cherche dans *M* la valeur *M[i][j]* minimale, représentant la distance entre les noeuds de l'arbre les plus proches. Puis on construit un nouveau noeud *noeud<sub>n+k</sub>* qui a pour fils les noeuds pointés par les *i<sup>ème</sup>* et *j<sup>ème</sup>* maillons de la liste *racines*. On ajoute un nouveau maillon à la fin de la liste *racines* contenant pour valeur le noeud *noeud<sub>n+k</sub>*.<br>
  On met ensuite à jour la matrice *M* afin de refléter les distances entre le nouveau noeud *noeud<sub>n+k</sub>* et les autres noeuds pointés par les maillons de la liste *racines*, tout en supprimant les lignes et colonnes de *M* associées aux noeuds pointés par les *i<sup>ème</sup>* et *j<sup>ème</sup>* maillons de la liste *racines*. Les *i<sup>ème</sup>* et *j<sup>ème</sup>* maillons de la liste *racines* seront également supprimés.<br>
  La distance d(*noeud<sub>n+k</sub>*, *noeud<sub>l</sub>*) entre le noeud crée *noeud<sub>n+k</sub>* et chaque autre noeud *noeud<sub>l</sub>* associé à *M* est calculée de la façon suivante :<br>
d(*noeud<sub>n+k</sub>*, *noeud<sub>l</sub>*) = ( d(**Element**(*racine, i), noeud<sub>l</sub>*) + d(**Element**(*racine, j), noeud<sub>l</sub>*) ) / 2. <br>
où **Element**(*racines, k*) est le noeud pointé par le *k<sup>ème</sup>* maillon de *racines*.<br>

Après *n*-2 itérations, on obtient deux sous-arbres frères qu'il faut lier à la racine de l'arbre. Finalement, on obtient un arbre phylogénétique des *n* gènes de départ. Cet arbre est raciné et binaire.

## 2 Affichage
### 2.1 Matrice de distances et liste des racines

La matrice de distances obtenue par l'algorithme UPGMA est affichée à chaque itération, ainsi que la liste *racines*.

### 2.2 Arbre binaire

L'algorithme UPGMA retourne un arbre binaire raciné dont les feuilles sont les noeuds de départ. Il est tout à fait possible de lui appliquer les parcours connus (dans l'ordre infixe, préfixe et postfixe). Néanmoins, ces parcours affichent également les noeuds supplémentaires obtenus à chaque itération UPGMA. Il serait plus informatif de n'afficher que les noeuds de départ regroupés de façon à refléter les distances phylogénétiques. <br>
C'est pourquoi l'affichage choisi reflète les relations phylogénétiques à l'aide de parenthésages. Par exemple : (1 4) ( ( 2 ( 0 3) ) ).
