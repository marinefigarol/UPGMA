/* matrice.h */

#ifndef MATRICE_H
#define MATRICE_H

#define TAILLE_MATRICE 5

float **nouvelle_matrice(int lignes, int colonnes) ;
void remplit_mat_init(size_t taille, float (**matrice)) ;
void print_mat(size_t taille, float (**matrice)) ;
void free_matrice (size_t taille, float (**mat)) ;
float **mise_a_jour(float (**M), size_t taille, int ligne, int colonne) ;


#endif /* matrice.h */
