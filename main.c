#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "liste.h"
#include "arbre.h"
#include "matrice.h"
#include "upgma.h"

/*
 * USAGE : utiliser le makefile (make puis ./main)
 * appel a Valgrind : valgrind --track-origins=yes --leak-check=full ./main
 */
 

/*
 * Ce programme permet la construction d'un arbre phylogénétique basé sur
 * la méthode UPGMA, à partir d'une matrice de distance. Il affiche la matrice
 * de distance initiale, puis la matrice modifiée ainsi que les racines
 * associées à l'arbre en construction à partir de cette matrice au fur et
 * à mesure. A la fin, l'arbre phylogénétique sous forme d'une liste parenthésée
 * reflétant les relations de parenté est affiché.
 */
int main()
{
	/* Creation d'une matrice 5*5 initiale */
	float **mat = nouvelle_matrice(TAILLE_MATRICE, TAILLE_MATRICE);
	/* Remplissage de la matrice */
	remplit_mat_init(TAILLE_MATRICE, mat);
	/* Affichage de la matrice de distance initiale */
	printf("\nMatrice initiale de distance (%d x %d)\n", TAILLE_MATRICE, 
			TAILLE_MATRICE) ;
	printf("-----------------------------------------------") ;
	print_mat(TAILLE_MATRICE, mat) ;
	/* Récupération de l'arbre créé à partir de la fonction upgma */
   	Arbre *A = upgma(TAILLE_MATRICE, mat) ;
   	/* Affichage de l'arbre sous forme d'une liste parenthésée */
   	print_arbre(A) ;
   	/*Désallocation de l'arbre */
	free_arbre(A) ;
	
	return 0;
}
