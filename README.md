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
