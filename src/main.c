#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/latex.h"
#include "../include/file.h"

char* parseCommandLine(int argc, char**argv)
{
	if(argc>1)
	{
		int i=0;
		char nom[strlen(argv[1])+1];
		for(i=0;i<strlen(argv[1]);i++)
		{
			nom[i]=argv[1][i];
		}
		nom[strlen(argv[1])]='\0';
		char prefix[]="./txtfiles/";
		char suffixe[]=".txt";
		int taille_chaine=strlen(prefix)+strlen(suffixe)+strlen(nom);
		char *chaine=(char*)malloc(sizeof(char)*taille_chaine);
		strcat(chaine,prefix);
		strcat(chaine,nom);
		strcat(chaine,suffixe);
		return chaine;
	}
	else
	{
		return NULL;
	}
}

int main(int argc, char**argv)
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
//     to_latex_pdf(my_vertices, my_edges, tex);
    to_latex_pdf(g->vertices, g->edges, tex);
    
    delete_edges(&(g->edges));
    delete_vertices(&(g->vertices));
    free(g);
#endif

#ifdef RODOLPHE
	
    Graphe* g= extractFile(parseCommandLine(argc,argv));
    array_edges* mst=kruskal(g);
#endif
    
	return 0;
}	
