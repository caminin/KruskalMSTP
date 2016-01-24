#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/graphe.h"
#include "../include/latex.h"
#include "../include/file.h"

int main(int argc, char**argv)
{
#ifdef FLORIAN
    char filename[]="./txtfiles/DAVID_Florian.txt";
    Graphe* g= extractFile(filename);
    
    array_edges* mst=kruskal(g);
    
    delete_edges(&(g->edges));
    g->edges= *mst;
    MST_to_latex_pdf(g, filename);
    
    delete_vertices(&(g->vertices));
    free(g);
    system("./bin/show_pdf.sh");
#endif

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
#endif

#ifdef RELEASE
    char filename="./txtfiles/DAVID_Florian.txt";
    Graphe* g= extractFile(chaine);
    
    array_edges* mst=kruskal(g);
    
    delete_edges(&(g->edges));
    g->edges= *mst;
    MST_to_latex_pdf(g, tex);
    
    delete_vertices(&(g->vertices));
    delete_edges(&(g->edges));
    free(g);
    system("./bin/show_pdf_quiet.sh");
#endif
    
	return 0;
}	
