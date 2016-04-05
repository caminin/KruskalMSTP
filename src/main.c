#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/graphe.h"
#include "../include/latex.h"
#include "../include/file.h"

int main(int argc, char**argv)
{
    char* filename="./DAVID_Florian.txt";
    Graphe* g= extractFile(filename);
    full_graphe_to_latex_pdf(g, filename);
    
    array_edges* mst=kruskal(g);
    
    delete_edges(&(g->edges));
    g->edges= *mst;
    MST_to_latex_pdf(g, filename);
    
    delete_vertices(&(g->vertices));
    delete_edges(mst);
    free(mst);
    free(g);
    
    return 0;
}	
