#ifndef EDGE_H
#define EDGE_H

#include "vertice.h"

typedef struct s_edge {
    int first_v;
    int second_v;
    float cost; // un double ne semble pas utile
    
}edge;

typedef struct s_array_edges{
    int nb_edges;
    edge** edges;
    
    
    
}array_edges;

//edge
void display_edge(struct s_edge);

// array_edges
void swap(array_edges*, int i, int j);
void init_size_edges(array_edges*, int size);
void add_edge(array_edges*, int num_first, int num_second, float cost, int pos);
edge* get_edge(array_edges, int pos);
void display_edges(array_edges *my_edges,int nb_egdes);
void mysort(array_edges *my_edges,int nb_cote);
void delete_edges(array_edges* ae);

#endif // EDGE_H
