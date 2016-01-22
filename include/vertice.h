#ifndef VERTICE_H
#define VERTICE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_vertice {
    int pos_x;
    int pos_y;
}vertice;

typedef struct s_array_vertices {
    int nb_vertices;
    vertice** vertices;    
}array_vertices;

void display_vertice(vertice v);
void init_size_vertices(array_vertices* av, int size);
void add_vertice(array_vertices* av, int x, int y, int pos);
vertice* get_vertice(array_vertices av, int pos);

#endif // VERTICE_H
