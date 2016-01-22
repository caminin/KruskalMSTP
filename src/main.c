#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/graphe.h"
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
#endif

#ifdef RODOLPHE
	
    Graphe* g= extractFile(parseCommandLine(argc,argv));
    array_edges* mst=kruskal(g);
#endif
    
	return 0;
}	
