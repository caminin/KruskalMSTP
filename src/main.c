#include <stdio.h>
#include <stdlib.h>
#include <boost/concept_check.hpp>

typedef struct s_vertice {
    int pox_x;
    int pox_y;
    
    void display(){
	printf("mon vertice est en pos %d ; %d\n", pox_x, pox_y);
    }
}vertice;

typedef struct s_edge {
    int first_v;
    int second_v;
    float cost; // un double ne semble pas utile
    
    void display(){
	printf("mon arc relie les sommets %d et %d avec un coût de %.3f\n", first_v, second_v, cost);
    }
}edge;

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
    
}array_edges;

int main(int argc, char **argv) {
    array_vertices my_vertices;
    my_vertices.init_size(10);
    my_vertices.add_vertice(1,2,0);
    
    vertice* vert_tmp= my_vertices.at(0);
    
    if (vert_tmp != NULL) {
	vert_tmp->display();
    }
    else { printf("VERTICE NULL"); }
    
    array_edges my_edges;
    my_edges.init_size(10);
    my_edges.add_edge(1,2, 2.5,0);
    
    
    edge* edge_tmp= my_edges.at(0);
    if (edge_tmp != NULL) {
	edge_tmp->display();
    }
    else { printf("VERTICE NULL"); }
    
    return 0;
}