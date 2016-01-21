#ifndef EDGE_H
#define EDGE_H

#include <stdio.h>

#include "vertice.h"

typedef struct s_edge {
    int first_v;
    int second_v;
    float cost; // un double ne semble pas utile
    
    void display(){
	printf("mon arc relie les sommets %d et %d avec un coût de %.3f\n", first_v, second_v, cost);
    }
}edge;

typedef struct s_array_edges{
    unsigned nb_edges;

    edge** edges;
    
    void init_size(unsigned size){
	nb_edges = size;
	edges= (edge**)malloc(size*(sizeof(edge*)));
    }
    
    void add_edge(int num_first, int num_second, float cost, unsigned pos){
	if (pos < nb_edges){
	    printf("DEBUG : Element ajouté en position %u\n", pos);
	    edge* new_edge= (edge*)malloc(sizeof(edge));
	    new_edge->first_v = num_first;
	    new_edge->second_v = num_second;
	    new_edge->cost = cost;
	    edges[pos]= new_edge;
	}
	else {
	    printf("ERROR : Position d'ajout de l'arc supérieure au nombre d'éléments\n");
	}
    }
    
    edge* at(unsigned pos){
	if (pos < nb_edges)
	    return edges[pos];
	else return NULL;
    }
        
    void swap(int i, int j)
    {
	    edge temp;
	    temp.first_v=edges[i]->first_v;
	    temp.second_v=edges[i]->second_v;
	    temp.cost=edges[i]->cost;
	    
	    edges[i]->first_v=edges[j]->first_v;
	    edges[i]->second_v=edges[j]->second_v;
	    edges[i]->cost=edges[j]->cost;
	    
	    edges[j]->first_v=temp.first_v;
	    edges[j]->second_v=temp.second_v;
	    edges[j]->cost=temp.cost;
    }
    
}array_edges;

#endif // EDGE_H
