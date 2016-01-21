#include <string.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct s_vertice {
    int pox_x;
    int pox_y;
    
    void display(){
	printf("mon vertice est en pos %d ; %d\n", pox_x, pox_y);
    }
}vertice;

typedef struct s_edge {
    int first_v;
    int second_v;
    float cost; // un double ne semble pas utile
    
    void display(){
	printf("mon arc relie les sommets %d et %d avec un coût de %.3f\n", first_v, second_v, cost);
    }
}edge;

typedef struct s_array_vertices {
    unsigned nb_vertices;

    vertice** vertices;
    
    void init_size(unsigned size){
	nb_vertices = size;
	vertices= (vertice**)malloc(size*(sizeof(vertice*)));
    }
    
    void add_vertice(int x, int y, unsigned pos){
	if (pos < nb_vertices){
	    printf("DEBUG : Element ajouté en position %u\n", pos);
	    vertice* new_vertice= (vertice*)malloc(sizeof(vertice));
	    new_vertice->pox_x = x;
	    new_vertice->pox_y = y;
	    vertices[pos]= new_vertice;
	}
	else {
	    printf("ERROR : Position d'ajout du sommet supérieure au nombre d'éléments\n");
	}
    }
    
    vertice* at(unsigned pos){
	if (pos < nb_vertices)
	    return vertices[pos];
	else return NULL;
    }
    
}array_vertices;


typedef struct s_array_edges{
    unsigned nb_edges;

    edge** edges;
    
    void init_size(unsigned size){
	nb_edges = size;
	edges= (edge**)malloc(size*(sizeof(edge*)));
    }
    
    void add_edge(int num_first, int num_second, float cost, unsigned pos){
	if (pos < nb_edges){
	    printf("DEBUG : Element ajouté en position %u\n", pos);
	    edge* new_edge= (edge*)malloc(sizeof(edge));
	    new_edge->first_v = num_first;
	    new_edge->second_v = num_second;
	    new_edge->cost = cost;
	    edges[pos]= new_edge;
	}
	else {
	    printf("ERROR : Position d'ajout de l'arc supérieure au nombre d'éléments\n");
	}
    }
    
    edge* at(unsigned pos){
	if (pos < nb_edges)
	    return edges[pos];
	else return NULL;
    }
    
}array_edges;

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
	array_vertices my_vertices;
    my_vertices.init_size(10);
    my_vertices.add_vertice(1,2,0);
    
    vertice* vert_tmp= my_vertices.at(0);
    
    if (vert_tmp != NULL) {
	vert_tmp->display();
    }
    else { printf("VERTICE NULL"); }
    
    array_edges my_edges;
    my_edges.init_size(10);
    my_edges.add_edge(1,2, 2.5,0);
    
    
    edge* edge_tmp= my_edges.at(0);
    if (edge_tmp != NULL) {
	edge_tmp->display();
    }
    else { printf("VERTICE NULL"); }
    
	char chaine[]="CHARLOT_Rodolphe.txt";
	extractFile(chaine);
	return 0;
}	
