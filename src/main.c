#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/graphe.h"
#include "../include/latex.h"
#include "../include/file.h"

int main(int argc, char**argv)
{
#ifdef RODOLPHE
	char chaine[]="./txtfiles/TROYSI_Morgane.txt";
    Graphe* g= extractFile(chaine);
    
    // LATEX
    FILE* tex= fopen("./obj/feuille.tex", "w");
    
    array_edges* mst=kruskal(g);
    
    delete_edges(&(g->edges));
    g->edges= *mst;
    MST_to_latex_pdf(g, tex);
    
    delete_vertices(&(g->vertices));
    free(g);
    system("./bin/show_pdf.sh");
#else
    char* filename="./txtfiles/DAVID_Florian.txt";
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
    system("./show_pdf_DAVID_Florian.sh");
#endif
    
	return 0;
}	
