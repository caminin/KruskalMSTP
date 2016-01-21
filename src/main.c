#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

void extractFile(char s[])
{
	int taille=get_file_size(s);	
	FILE *fichier;
	fichier=fopen(s,"r");
	
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
		int nb_cote=atoi(ligne1[1]);
		
		printf("%d, %d",nb_noeuds,nb_cote);
	}
	else
	{
	  // On affiche un message d'erreur si on veut
	  printf("Impossible d'ouvrir le fichier \n");
	}
	
	
}

int main()
{
	char chaine[]="CHARLOT_Rodolphe.txt";
	extractFile(chaine);
	return 0;
}	


