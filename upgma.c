#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "liste.h"
#include "arbre.h"
#include "matrice.h"
#include "upgma.h"

/*
 * Permet de créer un arbre phylogénétique raciné avec n feuilles à partir
 * d'une matrice de distance M de taille n*n.
 */
void *upgma(size_t n, float (**M))
{
    Arbre *arbre = nouvel_arbre() ;
    Liste *racines = nouvelle_liste() ;
    
    /* Creation des feuilles de l'arbre qui seront stockés dans la liste */
    for (int i = 0 ; i < n ; i++)
    {
		    Noeud *noeud = nouveau_noeud(i) ;
		    ajout_element_fin(racines, noeud, i) ;
	}
	
	printf("racines :") ;
	print_racine(racines) ;
	
	/* Compte le nombre de passage dans la boucle */
	int iteration = 0 ;
	
	for (int k = 0 ; k < n-2 ; k++)
	{
		
		/* Recherche de la position de la plus petite valeur de M */
		int min = INT_MAX;  /* initilisation du min : valeur infinie */
	    int i = 0 ;			/* Initialisation ligne du min */
	    int j = 0 ;			/* Initialisation colonne du min */

		/* Parcourt les lignes de la matrice */
		for (int ligne = 0; ligne < n-k ; ligne++)
		{
			/* Parcourt les colonnes de la matrice */
			for (int col = 0; col < n-k ; col++)
			{
				/*
				 * Si on trouve une valeur plus petite que le min qui n'est
				 * pas la valeur 0 (car ce sont les diagonales), on récupère
				 * les coordonnées de cette valeur.
				 */
				if (M[ligne][col] < min && M[ligne][col] != 0)
				{
					min = M[ligne][col];
	                i = ligne ;
	                j = col ;
				}
			}
		}
		
		/* Creation d'un nouveau noeud de valeur n+k */
		Noeud *new_noeud = nouveau_noeud(n+k) ;
		new_noeud -> gauche = Element(racines, i) ;
		new_noeud -> droit = Element(racines, j) ;
		ajout_element_fin(racines, new_noeud, n+k) ;
		
		/* Mise a jour de la matrice avec le nouveau noeud */
		M = mise_a_jour(M, n-k, i, j) ;

		supp_element(racines, j) ;
		supp_element(racines, i) ;
		
		iteration ++ ;
		
		printf("\n===============================================") ;
		printf("\nItération k = %d\n", k) ;
		printf("Nouvelle matrice de distances : (%zu x %zu)\n", n-k-1, n-k-1) ;
		printf("-----------------------------------------------") ;
		print_mat(n-k-1, M) ;
		printf("racines :") ;
		print_racine(racines) ;

	}
	
	/* On termine par la creation de la racine */
	Noeud *root = nouveau_noeud(n + iteration) ;
	root -> gauche = Element(racines, 0) ;
	root -> droit = Element(racines, 1) ;
	arbre -> racine = root ;
	
	/* On libère la mémoire allouée pour la liste et la dernière matrice */
	free_liste(racines);
	free_matrice(n-iteration, M) ;
	
	return(arbre) ;
}
