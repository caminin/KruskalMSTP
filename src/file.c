#include "../include/file.h"



int get_file_size(char *file_name)
{
   FILE *fp;
   int file_size;
   file_size = 0;
   if ((fp = fopen(file_name, "rb" )) == NULL) {
      fprintf(stderr, "Cannot open %s.\n", file_name);
      return(file_size);
   }
   char ligne[30];
   while(fgets(ligne, 30,fp) != NULL)
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

Graphe* extractFile(char s[])
{
	int size=get_file_size(s);	
	FILE *fichier;
	fichier=fopen(s,"r");
	
	Graphe* graphe= (Graphe*)malloc(sizeof(Graphe));
	
	if (fichier != NULL)
	{		
		char ** text=(char**)malloc(sizeof(char*)*size);
		char ligne[30];
		int num_ligne;
		for(num_ligne=0; fgets(ligne, 30,fichier) != NULL;
		    ++num_ligne)
		{
			text[num_ligne]=(char*)malloc(sizeof(char)*(strlen(ligne)+1));
			strcpy(text[num_ligne],ligne);
#ifdef DEBUG
			printf("DEBUG : num_ligne du fichier : %d/%d de valeur %s", num_ligne, size ,text[num_ligne]);
#endif
		}
		
		char **ligne1=str_split(text[0],' ');
		int nb_noeuds=atoi(ligne1[0]);
		init_size_vertices(&(graphe->vertices), nb_noeuds);
		
		int nb_cote=atoi(ligne1[1]);
		init_size_edges(&(graphe->edges), nb_cote);
		
		free(ligne1);
		
		int i;
		for(i=1;i<nb_noeuds+1;i++)
		{
			char **ligne1=str_split(text[i],' ');
			int coord_x=atoi(ligne1[0]);
			int coord_y=atoi(ligne1[1]);
			
			add_vertice(&(graphe->vertices), coord_x,coord_y,i-1);
			free(ligne1);
		}
		
		for(;i<nb_noeuds+nb_cote+1;i++)
		{
			char **ligne1=str_split(text[i],' ');
			int coord_x=atoi(ligne1[0]);
			int coord_y=atoi(ligne1[1]);
			float valeur=atof(ligne1[2]);
			
			add_edge(&(graphe->edges), coord_x,coord_y, valeur,i-nb_noeuds-1);
			free(ligne1);
		}
		printf("\nNUMERO DE LIGNE A LA SORTIE : %d\n", num_ligne);
		
		for (i= 0; i < size; ++i){
		    free(text[i]);
		}
		free(text);
		fclose(fichier);
#ifdef DEBUG
	printf("Je sors de extractFile\n");
#endif
	}
	else
	{
	  // On affiche un message d'erreur si on veut
	  fprintf(stderr, "%s\n","Impossible d'ouvrir le fichier \n");
	}
	return graphe;
}
