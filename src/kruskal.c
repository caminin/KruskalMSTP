#include "../include/kruskal.h"

int path_compression(subset mysubset[],int i)
{
	if (mysubset[i].father != i)
	{
		mysubset[i].father = path_compression(mysubset, mysubset[i].father);
	}
	return mysubset[i].father;
}

void subset_union(subset* subsets, int x, int y)
{
	int xroot = path_compression(subsets, x);
	int yroot = path_compression(subsets, y);
 
    // Attach smaller rank tree under root of high rank tree
    // (Union by Rank)
    if (subsets[xroot].value < subsets[yroot].value)
        subsets[xroot].father = yroot;
    else if (subsets[xroot].value > subsets[yroot].value)
        subsets[yroot].father = xroot;
 
    // If ranks are same, then make one as root and increment
    // its rank by one
    else
    {
        subsets[yroot].father = xroot;
        subsets[xroot].value++;
    }
}

array_edges* kruskal(Graphe *graphe)
{
	int nb_vertices= graphe->vertices.nb_vertices;
	int nb_edges= graphe->edges.nb_edges;
	
	mysort(&(graphe->edges), nb_edges);
	array_edges* mst=(array_edges*)malloc(sizeof(array_edges));
	// Number of edges initialized at the number of vertices -1
	// (number of edges of the final mst)
	init_size_edges(mst, nb_vertices-1);
	int taille_mst=0;
	int noeud_actuel=0;
	subset mysubset[nb_vertices-1];
	int i;
	for(i=0;i<nb_vertices;i++)
	{
		mysubset[i].father=i;
		mysubset[i].value=0;
	}
	
	while(taille_mst < (nb_vertices-1))
	{
		edge *actual_edge=get_edge(graphe->edges, noeud_actuel);
		noeud_actuel++;
		
		int compressed_children=path_compression(mysubset,actual_edge->first_v-1);
		int compressed_father=path_compression(mysubset,actual_edge->second_v-1);
		if(compressed_children != compressed_father)
		{
			add_edge(mst, actual_edge->first_v,actual_edge->second_v,actual_edge->cost,taille_mst);
			taille_mst++;
			subset_union(mysubset,compressed_children,compressed_father);
		}
	}
	
	int total_weight=0;
	int nb;
#ifdef DEBUG
	display_edges(mst,taille_mst);
	for(nb=0;nb<taille_mst;nb++)
	{
		total_weight+=(get_edge(*mst, nb))->cost;
	}
	printf("Le cout total est de %d\n",(int) total_weight);
#endif
	
	return mst;
}
