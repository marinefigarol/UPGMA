/* liste.h */

#include "arbre.h"
#ifndef LISTE_H
#define LISTE_H

typedef struct Maillon Maillon;
typedef struct Liste Liste;

struct Maillon {
    Maillon *suivant;
    Noeud *valeur ; /* pointeur vers la noeud d'un arbre */
};


struct Liste {
    Maillon *tete;
};


Liste *nouvelle_liste() ;
Maillon *nouveau_maillon(Noeud *noeud) ;
void ajout_element_debut(Liste *L, Noeud *noeud) ;
void ajout_element_fin(Liste *L, Noeud *noeud, int val) ;
void supp_element_debut(Liste *L) ;
void supp_element_fin(Liste *L) ;
int supp_element(Liste *L, int k) ;
Noeud *trouver_dernier_maillon(Liste *L) ;
void free_liste(Liste *liste)  ;

Noeud *Element (Liste *L, int i) ;
void print_racine(Liste *L) ;


#endif /* liste.h */
