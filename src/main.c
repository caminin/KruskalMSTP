#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/latex.h"
#include "../include/file.h"


int main()
{
	
#ifdef FLORIAN
    // Initialisations
//     array_vertices my_vertices;
//     array_edges my_edges;
    
/*** 	TESTS	 ***/

    /* Tests pour chargement fichier */
    char chaine[]="./txtfiles/DAVID_Florian.txt";
    Graphe* g= extractFile(chaine);
    
    
//     array_edges* mst_kruskal= kruskal(g);

    /* Tests pour création fichier LATEX */
    FILE* tex= fopen("feuille.tex", "w"); /*= to_latex(my_vertices, my_edges, "exemple_feuille.tex");*/    
    full_graphe_to_latex_pdf(g, tex);
    
    delete_edges(&(g->edges));
    delete_vertices(&(g->vertices));
    free(g);
#endif

#ifdef RODOLPHE
	char chaine[]="./txtfiles/GARNIER_Antoine.txt";
    Graphe* g= extractFile(chaine);
    array_edges* mst=kruskal(g);
#endif
    
	return 0;
}	
