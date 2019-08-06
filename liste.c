#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "arbre.h"
#include "liste.h"



/* crée une nouvelle liste qui pointe à NULL */
Liste *nouvelle_liste() 
{
	Liste *l = (Liste*)malloc(sizeof(Liste)) ;
	
	if (!l)
	{
		fprintf(stderr, "L'allocation de mémoire a échouée !\n");
		exit(EXIT_FAILURE);
	}
	
	l -> tete = NULL;
    return l;
}

/* crée un nouveau maillon qui a pour valeur un pointeur sur un noeud */
Maillon *nouveau_maillon(Noeud *noeud) 
{
	Maillon *m = (Maillon *)malloc(sizeof(Maillon));
	
		if (!m)
	{
		fprintf(stderr, "L'allocation de mémoire a échouée !\n");
		exit(EXIT_FAILURE);
	}
	
	m -> suivant = NULL;
	m -> valeur = noeud ;
    return m;
}



/* ajoute un élément de valeur val au début de la liste */
void ajout_element_debut(Liste *L, Noeud *noeud) 
{
	Maillon *new = nouveau_maillon(noeud);
	new -> suivant = L -> tete;
	L -> tete = new;
}

/*
 * ajoute un élément de valeur val à la fin de la liste
 */
void ajout_element_fin(Liste *L, Noeud *noeud, int val) 
{
	if (L == NULL)
	{
		printf ("La liste est vide\n");
		return;
	}
	
	Maillon *new = nouveau_maillon(noeud);
	if (L -> tete == NULL)
	{
		L -> tete = new;
	}
	
	else
	{
		Maillon *p = L -> tete;
		while (p -> suivant != NULL)
		{
			p = p -> suivant;
		}
		p -> suivant = new;
	}
}


/*
 * supprime le premier élément de la liste
 */
void supp_element_debut(Liste *L) 
{
	if (!L)
	{
		printf ("La liste est vide\n");
		return;
	}
	
	if (L->tete)
	{
		Maillon *p = L -> tete;
		L -> tete = p -> suivant;
		free(p);
	}    
}

/*
 * supprime le dernier élément de la liste
 */
void supp_element_fin(Liste *L) 
{
	if (!L) return;
	
	if (L->tete)
	{
		if (L -> tete -> suivant == NULL)
		{
			supp_element_debut(L);
		}
		
		else
		{
			Maillon *p = L -> tete;
			Maillon *q = p;
			while (p -> suivant != NULL)
			{
				q = p;
				p = p -> suivant;
			}
			free(p);
			q -> suivant = NULL;
		}
	}
}

/*
 * supprime le k-ième élément de la liste (on suppose que la première place
 * est 0); si c'est possible, on modifie la liste et on retourne 1 ; sinon,
 * on ne modifie pas la liste, on retourne 0 et on sort de la fonction
 */
int supp_element(Liste *L, int k) 
{
	if (k < 0) return 0 ;
	
	if (k == 0)
	{
		supp_element_debut(L);
		return 1 ;
	}
	
	if (!L) return 0;
	
	else if (L -> tete)
	{
		int a = 0;
		Maillon *p = L -> tete;
		Maillon *q = p;
		
		while (a < k && p -> suivant != NULL)
		{
			q = p;
			p = p -> suivant;
			a++;
		}
		
		if (p -> suivant == NULL)
		{
			supp_element_fin(L);
		}
		
		else if (a == k)
		{
			q -> suivant = p -> suivant;
			free(p);
			return 1 ;
		}
	}
	return 1 ;
}
/*
 * Retourne le dernier noeud pointé dans la liste chainée
 */
Noeud *trouver_dernier_maillon(Liste *L)
{
	if (!L)
	{
		return 0;
	}
    Maillon *p = L -> tete;
    while (p -> suivant != NULL)
    {
        p = p -> suivant;
    }
    return (p -> valeur);
}


/*
 * Désalloue la mémoire allouée pour la liste qui stocke les racines.
 */
void free_liste(Liste *liste) 
{
	Maillon *p, *q;
	/* le pointeur p parcourt la liste en allant un maillon plus loin que q. 
	 * On désaloue le maillon pointé par q au fur et à mesure, jusqu'à ce que
	 * p soit à NULL, ie la liste soit vide */
	 
	 if (!liste)
	 {
		 return; /* si la liste est vide, on sort de la fonction */
	 }
	 if (liste -> tete)
	 {
		 p = liste -> tete;
		 while (p)
		 {
			 q = p;
			 p = p -> suivant;
			 free(q);
		 } 
	 }
	 free(liste);
}


/*
 * Retourne le noeud pointé par le i-ème maillon de L s'il existe ou NULL
 * sinon.
 */
Noeud *Element (Liste *L, int i)
{
	Maillon *pointeur = L -> tete ;
	
	if (i == 0) return (pointeur -> valeur) ;
	
	int compteur = 0 ;
	while (pointeur != NULL && compteur < i)
	{
		pointeur = pointeur -> suivant ;
		compteur++ ;
	}
	
	if (pointeur == NULL)
	{
		return NULL ;
	}
	return (pointeur -> valeur) ;
}


/*
 * Permet l'affichage de la liste des racines pointées dans la liste L.
 */
void print_racine(Liste *L)
{
	Maillon *pointeur = L -> tete ;
	printf("( ") ;
	while (pointeur != NULL)
	{
		printf("%d ", pointeur -> valeur -> cle) ;
		pointeur = pointeur -> suivant ;
	}
	printf(")") ;
}
