#include "../include/vertice.h"

// VERTICE
void display_vertice(vertice v)
{
	printf("mon vertice est en pos %d ; %d\n", v.pos_x, v.pos_y);
}


// ARRAY_VERTICES
void init_size_vertices(struct s_array_vertices* av, int size)
{
    av->nb_vertices = size;
    av->vertices= (vertice**)malloc(size*(sizeof(vertice*)));
}

void add_vertice(struct s_array_vertices* av, int x, int y, int pos)
{
    if (pos < av->nb_vertices){
	printf("DEBUG : Sommet ajouté en position %u\n", pos);
	vertice* new_vertice= (vertice*)malloc(sizeof(vertice));
	new_vertice->pos_x = x;
	new_vertice->pos_y = y;
	av->vertices[pos]= new_vertice;
    }
    else {
	printf("ERROR : Position d'ajout du sommet supérieure au nombre d'éléments\n");
    }
}

vertice* get_vertice(struct s_array_vertices av, int pos){
    if (pos < av.nb_vertices)
	return av.vertices[pos];
    else return NULL;
}
