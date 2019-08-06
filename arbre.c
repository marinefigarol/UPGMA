#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "arbre.h"

/* ======================= Allocation mémoire ============================ */

/* 
 * Crée un nouvel arbre binaire dont la racine est à NULL et renvoie un 
 * pointeur vers cet arbre.
 */
Arbre *nouvel_arbre() {
	Arbre *arbre = (Arbre*)malloc(sizeof(Arbre)) ;
	if (!arbre)		/* Si le pointeur est null */
	{
		fprintf(stderr, "L'allocation de mémoire a échoué !\n") ;
		exit(EXIT_FAILURE) ;
	}
	arbre -> racine = NULL ;
    return arbre ;
}

/* 
 * Crée un nouveau noeud dont les fils gauche et droit sont à NULL et la
 * clé vaut val, et renvoie un pointeur vers ce noeud.
 */
Noeud *nouveau_noeud(int val) {
	Noeud *noeud = (Noeud*)malloc(sizeof(Noeud)) ;
	if (!noeud)		/* Si le pointeur est null */
	{
		fprintf(stderr, "L'allocation de mémoire a échoué !\n") ;
		exit(EXIT_FAILURE) ;
	}
	noeud -> gauche = NULL ;
	noeud -> droit = NULL ;
	noeud -> cle = val ;
    return noeud ;
}

/* ======================= Désallocation mémoire ============================ */

/* Libère la mémoire allouée a un arbre et a tous ses noeuds */
void free_arbre(Arbre *A) {
    if (A != NULL)
	{
		free_arbre_aux(A->racine) ;
		free(A) ;
	}
}

/* Libère la mémoire allouée aux noeuds */
void free_arbre_aux(Noeud *n) {
	if (n != NULL)
	{
		free_arbre_aux(n->gauche) ;
		free_arbre_aux(n->droit) ;
		free(n) ;
	}
}


/* ======================= Affichage Arbre ============================ */

/*
 * Affichage des feuilles de l'arbre raciné, reflétant les relations
 * phylogénétiques à l'aide de parenthésages.
 */
void print_arbre(Arbre *A)
{
	printf("\n===============================================") ;
	printf("\n\nArbre obtenu par la méthode UPGMA : \n") ;
    print_arbre_aux(A->racine) ;
    /*printf("\n") ;*/
    printf("\n\n===============================================\n") ;
}

/* Affichage des noeuds */
void print_arbre_aux(Noeud *n) {
	/* C'est une feuille */
	if (n != NULL && n -> gauche == NULL && n -> droit == NULL)
	{
		printf("%d ", n -> cle) ;
	}
	/*C'est un noeud interne */
	if (n -> gauche != NULL || n -> droit != NULL)
	{
		printf("( ") ;
		if (n -> gauche != NULL)
		{
			print_arbre_aux(n -> gauche) ;
		}
		if (n -> droit != NULL)
		{
			print_arbre_aux(n -> droit) ;
		}
		printf(")") ;
	}
}
