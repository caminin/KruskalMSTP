#ifndef __KRUSKAL_INCLUDED__
#define __KRUSKAL_INCLUDED__

#include "edge.h"

typedef struct s_subset {
	int father;
	int value;
} subset;

typedef struct s_graphe{
    array_vertices vertices;
    array_edges edges;
}Graphe;


int path_compression(subset mysubset[],int i);
void subset_union(subset* subsets, int x, int y);
array_edges* kruskal(Graphe *graphe);

#endif //__KRUSKAL_INCLUDED__

