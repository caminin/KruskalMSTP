#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/graphe.h"
#include "../include/latex.h"
#include "../include/file.h"

int main()
{
    char filename[]="./txtfiles/DAVID_Florian.txt";
    Graphe* g= extractFile(filename);
    
    // LATEX
    
    array_edges* mst=kruskal(g);
    
    delete_edges(&(g->edges));
    g->edges= *mst;
    MST_to_latex_pdf(g, filename);
    
    delete_vertices(&(g->vertices));
    free(g);
    
	return 0;
}	
