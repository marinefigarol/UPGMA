#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "arbre.h"
#include "liste.h"
#include "matrice.h"


/* Creation d'une matrice */
float **nouvelle_matrice(int lignes, int colonnes)
{
	/* Allocation de l'espace nécessaire pour les lignes de la matrice */
	float **matrice = (float **) malloc(lignes * sizeof(float *));
	if(matrice == NULL)
	{
		fprintf(stderr, "Mémoire insuffisante \n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < lignes; i++)
	{
		/* Allocation espace pour les colonnes */
		matrice[i] = (float *) malloc(colonnes * sizeof(float));
		if (matrice[i] == NULL)
		{
			fprintf(stderr, "Mémoire insuffisante \n");
			exit(EXIT_FAILURE);
		}
	}
	
	return matrice;
}



/* Fonction pour remplir la matrice avec les nombres de la prof */
void remplit_mat_init(size_t taille, float (**matrice))
{
	if (!matrice) return;
	
	 /* Parcourt les lignes de la matrice */
	for (int i = 0; i < (int)taille; i++)
	{
		/* Parcourt les colonnes de la matrice */
		for (int j = 0; j < (int)taille; j++)
		{
			/* La diagonale vaut 0 */
			if (j == i)
			{
				matrice[i][j] = 0.0;
			}
			else if ((i == 0 && j == 1) || (i == 1 && j == 0) ||
					(i == 4 && j == 1) || (i == 1 && j == 4))
			{
				matrice[i][j] = 2;
			}
			else if ((i == 2 && j == 0) || (i == 0 && j == 2) ||
					(i == 4 && j == 3) || (i == 3 && j == 4))
			{
				matrice [i][j] = 3;
			}
			else if ((i == 3 && j == 0) || (i == 0 && j == 3) ||
					(i == 3 && j ==2) || (i == 2 && j == 3))
			{
				matrice[i][j] = 1;
			}
			else if ((i == 0 && j == 4) || (i == 4 && j == 0))
			{
				matrice[i][j] = 6;
			}
			else if ((i == 2 && j == 1) || (i == 1 && j == 2))
			{
				matrice[i][j] = 7;
			}
			else if ((i == 3 && j == 1) || (i == 1 && j == 3))
			{
				matrice[i][j] = 4;
			}
			else if ((i == 4 && j == 2) || (i == 2 && j == 4))
			{
				matrice[i][j] = 8;
			}
		}
	}
}



/*  Fonction qui permet l'affichage de la matrice */
void print_mat(size_t taille, float (**matrice))
{
	for (int i = 0; i < taille; i++)
	{
		printf ("\n");
		for (int j = 0; j < taille; j++)
		{
			printf (" %.2f ", matrice[i][j]);
		}
	}
	printf ("\n");
}


/* fonction qui libère une matrice */
void free_matrice (size_t taille, float (**mat))
{
	for (int i = 0; i < taille; i++)
	{
		free(mat[i]);
	}
	free(mat);
}


/* 
 * Mise à jour de la matrice (diminution de la taille en supprimant les
 * lignes et colonnes de la plus petite valeur de la matrice de distance
 * et recalcule des distances). Retourne la nouvelle matrice.
 */
float **mise_a_jour(float (**M), size_t taille, int ligne, int colonne)
{
	
	/* Création de la nouvelle matrice */
	float **new_M = nouvelle_matrice(taille-1, taille-1) ;
	/* itérateurs indépendants pour la nouvelle matrice */
	int m = 0  ;					/* Parcourt ligne new_M */
	int n = 0 ;						/* Parcourt colonne de new_M */
	int iter = 0 ;					/* Pour remplir la dernière ligne/colonne */
	
	
	/* Parcourt des lignes de M */
	for (int i = 0 ; i < taille ; i++)
	{
		/* Si on a rempli une ligne de la nouvelle matrice, on change de
		 * ligne et on réinitialise les colonnes */
		if (n != 0)
		{
			m ++ ;
			n = 0 ;
		}
		/* Parcourt des colonnes de M */ 
		for (int j = 0 ; j < taille ; j++)
		{
			/* 
			 * On n'est pas sur une des lignes/colonnes de M que l'on doit
			 * supprimer on peut remplir une case de la nouvelle matrice
			 * (correspond aux valeurs qui ne changent pas dans la matrice)
			 */
			if (i != ligne && i != colonne && j != ligne && j != colonne)
			{
				new_M[m][n] = M[i][j] ;
				n ++ ;
			}
			/* On est sur une case dont on va devoir recalculer la distance 
			 * (correspond à la dernière ligne/colonne de la nouvelle
			 * matrice)
			 */
			else if (j == ligne && i != ligne && i != colonne)
			{
				new_M[taille-2][iter] = new_M[iter][taille-2] = (M[i][j]+M[i][colonne])/2 ;
				iter ++ ;
			}
		}
	}
	/* On remplit la dernière case de la nouvelle matrice qui ne l'a pas
	 * été
	 * */
	new_M[taille-2][taille-2] = 0 ;
	
	/* On libère l'ancienne matrice et on retourne la nouvelle */
	free_matrice(taille, M) ;
	return (new_M) ;
}
