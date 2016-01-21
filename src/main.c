#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "vertice.h"
#include "edge.h"
#include "latex.h"

typedef struct s_subset {
	int father;
	int value;
	
} subset;

int get_file_size(char *file_name)
{
   FILE *fp;
   int file_size;
   file_size = 0;
   if ((fp = fopen(file_name, "rb" )) == NULL) {
      fprintf(stderr, "Cannot open %s.\n", file_name);
      return(file_size);
   }
   char ligne[20];
   while(fgets(ligne, sizeof(char)*50,fp) != NULL)
	{
		file_size++;
	}
   fclose(fp);
   return(file_size);
}

char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result =(char**) malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        *(result + idx) = 0;
    }

    return result;
}



void mysort(array_edges *my_edges,int nb_cote)
{
	for(int i=0;i<nb_cote;i++)
	{
		for(int j=i;j<nb_cote;j++)
		{
			if(my_edges->at(i)->cost > my_edges->at(j)->cost)
			{
				my_edges->swap(i,j);
			}
		}
	}
}

void display(array_edges *my_edges,int nb_cote)
{
	for(int i=0;i<nb_cote;i++)
	{
		printf("%d de coordonnes : %d et %d \n",(int)(my_edges->at(i))->cost,(int)(my_edges->at(i))->first_v,(int)(my_edges->at(i))->second_v);
	}
}

int path_compression(subset *mysubset,unsigned i)
{
	if (mysubset[(int)i].father != i)
		mysubset[(int)i].father = path_compression(mysubset, mysubset[(int)i].father);
 
    return mysubset[(int)i].father;
}

void subset_union(subset* subsets, unsigned x, unsigned y)
{
	unsigned xroot = path_compression(subsets, x);
	unsigned yroot = path_compression(subsets, y);
 
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

void kruskal(array_vertices *my_vertices,int nb_noeuds,array_edges *my_edges,int nb_cote)
{
	mysort(my_edges,nb_cote);
	array_edges msp;
	msp.init_size(nb_cote-1);
	int taille_msp=0;
	int noeud_actuel=0;
	subset *mysubset=(subset*)malloc(sizeof(subset)*nb_noeuds);
	for(int i=0;i<nb_noeuds;i++)
	{
		mysubset[i].father=i;
		mysubset[i].value=0;
	}
	
	while(taille_msp < (nb_noeuds-1))
	{
		edge *actual_edge=my_edges->at(noeud_actuel);
		noeud_actuel++;
		
		unsigned compressed_children=path_compression(mysubset,actual_edge->first_v);
		unsigned compressed_father=path_compression(mysubset,actual_edge->second_v);
		if(compressed_children != compressed_father)
		{
			msp.add_edge(actual_edge->first_v,actual_edge->second_v,actual_edge->cost,taille_msp);
			taille_msp++;
			subset_union(mysubset,compressed_children,compressed_father);
		}
	}
	unsigned total_weight=0;
	
	for(unsigned nb=0;nb<taille_msp;nb++)
	{
		msp.at(nb)->display();
		total_weight+=msp.at(nb)->cost;
	}
	printf("Le cout total est de %d\n",(int) total_weight);
}

void extractFile(char s[])
{
	int taille=get_file_size(s);	
	FILE *fichier;
	fichier=fopen(s,"r");
	
	array_vertices my_vertices;
	array_edges my_edges;
	
	if (fichier != NULL)
	{		
		char ** text=(char**)malloc(sizeof(char*)*taille);
		char ligne[20];
		int num_ligne=0;
		while(fgets(ligne, sizeof(char)*50,fichier) != NULL)
		{
			text[num_ligne]=(char*)malloc(sizeof(char)*strlen(ligne));
			strcpy(text[num_ligne],ligne);
			printf("%s",text[num_ligne]);
			num_ligne++;
		}
		fclose(fichier);
		
		char **ligne1=str_split(text[0],' ');
		int nb_noeuds=atoi(ligne1[0]);
		my_vertices.init_size(nb_noeuds);
		
		int nb_cote=atoi(ligne1[1]);
		my_edges.init_size(nb_cote);
		
		for(int i=1;i<nb_noeuds+1;i++)
		{
			char **ligne1=str_split(text[i],' ');
			int coord_x=atoi(ligne1[0]);
			int coord_y=atoi(ligne1[1]);
			
			my_vertices.add_vertice(coord_x,coord_y,i-1);
		}
		
		for(int i=nb_noeuds+1;i<nb_noeuds+nb_cote+1;i++)
		{
			char **ligne1=str_split(text[i],' ');
			int coord_x=atoi(ligne1[0]);
			int coord_y=atoi(ligne1[1]);
			long valeur=atof(ligne1[2]);
			
			my_edges.add_edge(coord_x,coord_y, valeur,i-nb_noeuds-1);
		}
		
		kruskal(&my_vertices,nb_noeuds,&my_edges,nb_cote);
		
	}
	else
	{
	  // On affiche un message d'erreur si on veut
	  printf("Impossible d'ouvrir le fichier \n");
	}
	
}

int main()
{
    // Initialisations
    array_vertices my_vertices;
    array_edges my_edges;
    
/*** 	TESTS	 ***/
    /* Tests pour ajout */
    
    // Sommets
    my_vertices.init_size(4);
    my_vertices.add_vertice(1,0, 0);
    my_vertices.add_vertice(1,1, 1);
    my_vertices.add_vertice(0,1, 2);
    my_vertices.add_vertice(0,0, 3);
    
    vertice* vert_tmp= my_vertices.at(0);
    
    if (vert_tmp != NULL) {
	vert_tmp->display();
    }
    else { printf("VERTICE NULL"); }
    
    // Arcs
    my_edges.init_size(5);
    my_edges.add_edge(1,2, 3.14, 0);
    my_edges.add_edge(1,3, 12, 1);
    my_edges.add_edge(2,3, 3.5, 2);
    my_edges.add_edge(2,4, 1.05, 3);
    my_edges.add_edge(3,4, 2.8, 4);
    
    edge* edge_tmp= my_edges.at(0);
    if (edge_tmp != NULL) {
	edge_tmp->display();
    }
    else { printf("VERTICE NULL"); }
    
    /* Tests pour chargement fichier */
// 	char chaine[]="CHARLOT_Rodolphe.txt";
// 	extractFile(chaine);

    /* Tests pour création fichier LATEX */
    FILE* tex= fopen("exemple_feuille.tex", "w"); /*= to_latex(my_vertices, my_edges, "exemple_feuille.tex");*/
    to_latex_pdf(my_vertices, my_edges, tex);
    
    return 0;
}	
