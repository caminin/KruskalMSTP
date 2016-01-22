#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/graphe.h"
#include "../include/latex.h"
#include "../include/file.h"

int main()
{
    char chaine[]="./txtfiles/RAYER_Ugo.txt";
    Graphe* g= extractFile(chaine);
    
    // LATEX
    FILE* tex= fopen("feuille.tex", "w");
    
    array_edges* mst=kruskal(g);
    
    delete_edges(&(g->edges));
    g->edges= *mst;
    MST_to_latex_pdf(g, tex);
    
    delete_vertices(&(g->vertices));
    free(g);
    
	return 0;
}	
