#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/graphe.h"
#include "../include/latex.h"
#include "../include/file.h"

int main()
{
    char chaine[]="./txtfiles/GARNIER_Antoine.txt";
    Graphe* g= extractFile(chaine);
    
    // LATEX
    FILE* tex= fopen("feuille.tex", "w");
    
#ifdef FLORIAN
    /* Tests pour création fichier LATEX */
    full_graphe_to_latex_pdf(g, tex);

#endif

#ifdef RODOLPHE
    array_edges* mst=kruskal(g);
#endif
    
    delete_edges(&(g->edges));
    delete_vertices(&(g->vertices));
    free(g);
    
	return 0;
}	
