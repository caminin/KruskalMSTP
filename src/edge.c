#include "edge.h"

void display_edge(edge e){
    printf("mon arc relie les sommets %d et %d avec un coût de %.3f\n", e.first_v, e.second_v, e.cost);
}

    
void init_size_edges(array_edges* ae, unsigned size){
    ae->nb_edges = size;
    ae->edges= (edge**)malloc(size*(sizeof(edge*)));
}

void add_edge(array_edges* ae, int num_first, int num_second, float cost, unsigned pos){
    if (pos < ae->nb_edges){
	printf("DEBUG : Element ajouté en position %u\n", pos);
	edge* new_edge= (edge*)malloc(sizeof(edge));
	new_edge->first_v = num_first;
	new_edge->second_v = num_second;
	new_edge->cost = cost;
	ae->edges[pos]= new_edge;
    }
    else {
	printf("ERROR : Position d'ajout de l'arc supérieure au nombre d'éléments\n");
    }
}

edge* get_edge(array_edges ae, unsigned pos){
    if (pos < ae.nb_edges)
	return ae.edges[pos];
    else return NULL;
}

void display_edges(array_edges *my_edges,int nb_egdes)
{
	int i;
	for(i=0;i < nb_egdes;i++)
	{
		printf("%d de coordonnes : %d et %d \n",(int)(get_edge(*my_edges, i))->cost,(int)(get_edge(*my_edges, i))->first_v,(int)(get_edge(*my_edges, i))->second_v);
	}
}
    
void swap(array_edges* ae, int i, int j)
{
    if (ae== NULL) printf("ERROR ARRAY NULL, swap impossible\n");
    else {
	printf("DEBUG swap possible, taille : %ld\n", sizeof(*ae));
	if(get_edge(*ae, i) == NULL) printf("ERROR Arc non initialisé\n");
	else printf("ERROR Arc bien initialisé\n");
// 	edge temp = *(get_edge(*ae, i));
// 	temp.first_v=ae->edges[i]->first_v;
// 	temp.second_v=ae->edges[i]->second_v;
// 	temp.cost=ae->edges[i]->cost;
	
// 	ae->edges[i]->first_v=	ae->edges[j]->first_v;
// 	ae->edges[i]->second_v=	ae->edges[j]->second_v;
// 	ae->edges[i]->cost=ae->edges[j]->cost;
// 	
// 	ae->edges[j]->first_v=	temp.first_v;
// 	ae->edges[j]->second_v=	temp.second_v;
// 	ae->edges[j]->cost=temp.cost;
    }
}

void delete_edges(array_edges* ae)
{
    unsigned i;
    for (i= 0; i < ae->nb_edges ; ++i){
	free(get_edge(*ae, i));
    }
    free(ae->edges);
}

    