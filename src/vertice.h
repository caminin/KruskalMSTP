#ifndef VERTICE_H
#define VERTICE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct s_vertice {
    int pox_x;
    int pox_y;
    
    void display(){
	printf("mon vertice est en pos %d ; %d\n", pox_x, pox_y);
    }
}vertice;

typedef struct s_array_vertices {
    unsigned nb_vertices;

    vertice** vertices;
    
    void init_size(unsigned size){
	nb_vertices = size;
	vertices= (vertice**)malloc(size*(sizeof(vertice*)));
    }
    
    void add_vertice(int x, int y, unsigned pos){
	if (pos < nb_vertices){
	    printf("DEBUG : Element ajouté en position %u\n", pos);
	    vertice* new_vertice= (vertice*)malloc(sizeof(vertice));
	    new_vertice->pox_x = x;
	    new_vertice->pox_y = y;
	    vertices[pos]= new_vertice;
	}
	else {
	    printf("ERROR : Position d'ajout du sommet supérieure au nombre d'éléments\n");
	}
    }
    
    vertice* at(unsigned pos){
	if (pos < nb_vertices)
	    return vertices[pos];
	else return NULL;
    }
    
}array_vertices;


#endif // VERTICE_H
