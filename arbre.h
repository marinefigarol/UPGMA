/* abre.h */

#ifndef ARBRE_H
#define ARBRE_H

typedef struct Noeud Noeud;

struct Noeud {
    int cle;
    struct Noeud *gauche;
    struct Noeud *droit;
};

typedef struct Arbre {
    Noeud *racine;
} Arbre;

Arbre *nouvel_arbre() ;
Noeud *nouveau_noeud(int val) ;

void free_arbre(Arbre *A) ;
void free_arbre_aux(Noeud *n) ;

void print_arbre(Arbre *A) ;
void print_arbre_aux(Noeud *n) ;

#endif /* arbre.h */
