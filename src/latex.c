#include "../include/latex.h"

#define CIRCLE_RADIUS "1.0cm"
#define COEF_SIZE 1
#define SCALING "0.25"

void vertices_to_latex(array_vertices* av, FILE* file)
{
    fprintf(file, "%% vertices\n");
    int i;
    for (i= 0; i < av->nb_vertices; ++i){
	vertice* v= get_vertice(*av, i);
	// Positioning of the vertice
	fprintf(file, "\\cnode(%d,%d)", COEF_SIZE * v->pos_x, COEF_SIZE *v->pos_y);
	// Size and number of the vertice
	fprintf(file, "{%s}{%d}", CIRCLE_RADIUS, i+1);
	// TODO Number positioning
	fprintf(file, "\\rput(%d,%d)", COEF_SIZE *v->pos_x, COEF_SIZE *v->pos_y);
	// TODO Number display
	fprintf(file, "{\\tt %d}\n", i+1);
    }
}

void edges_to_latex(array_edges* ae, FILE* file)
{
    // Edges export
    fprintf(file, "%% edges\n");
    int i;
    for (i= 0; i < ae->nb_edges; ++i){
	edge* e= get_edge(*ae, i);
	// Edges drawing TODO que fait le {-} ?
	fprintf(file, "\\ncline{-}{%d}{%d}\n", e->first_v, e->second_v);
	/// The cost of each edges is not displayed
    }
}

void red_edges_to_latex(array_edges* ae, FILE* file)
{
    // Edges export
    fprintf(file, "%% edges of MST\n");
    int i;
// #ifdef DEBUG
    printf("Nb_edges : %d", ae->nb_edges);
// #endif
    for (i= 0; i < ae->nb_edges; ++i){
	edge* e= get_edge(*ae, i);
	// Edges drawing TODO que fait le {-} ?
	fprintf(file, "\\ncline[linecolor=red,linewidth = 3pt]{-}{%d}{%d}\n", e->first_v, e->second_v);
	/// The cost of each edges is not displayed
    }
}

char graphe_to_latex(Graphe* graphe, FILE* file, void (*func_to_latex)(array_edges* ae, FILE* file))
{
// 	file= fopen(filename,"w");
	
	if (file != NULL)
	{
	    fprintf(file, "\\begin{pspicture*}(-1,-1)(55,55)\n");
	    
	    vertices_to_latex(&(graphe->vertices), file);
	    func_to_latex(&(graphe->edges), file);
	    
	    // End of the LATEX file
	    fprintf(file, "\\end{pspicture*}");
	    
	    return 1;
	}
	
	else
	{
	  // On affiche un message d'erreur
	  printf("Impossible to create the output LATEX file\n");
	  return 0;
	}
}

#define MARGE "2cm"
void graphe_to_latex_pdf(Graphe* graphe, char* filename, void (*func_to_latex)(Graphe*, FILE*))
{
    // Replace extension by .tex
    int name_size= strlen(filename);
    
    char* extension= strrchr(filename, '.');
    int size_extension = strlen(extension);
    
    // Size of string : size filename - extension's size + size of ".tex" + 2
    char* tmp_str= (char*)malloc((name_size-size_extension+6)*sizeof(char));
    
    // Copy filename without extension, but with '.'
    strncpy(tmp_str, filename, name_size-size_extension+1);
    tmp_str[name_size-size_extension+1]= '\0';
    strcat(tmp_str, "tex");
    
    // Delete path to keep just the filename
    tmp_str= strrchr(tmp_str, '/');
    
    char* tex_filename[strlen(tmp_str)+2];
    if (tmp_str[0] == '/'){
	tmp_str[0]= '.';
	strcpy(tex_filename, "G");
    }
    else {
	strcpy(tex_filename, "G.");
    }
    strcat(tex_filename, tmp_str);
    
    
    printf("LATEX filename : %s\n", tex_filename);
    
    // File open in write mode
    FILE* file= fopen(tex_filename, "w");

    // Modification of filename to be able to print it in LATEX
	// Replace "_" by "\_" 
    const char s[2] = "_";
    char *token;
   
    token = strtok(tex_filename, s);
   
    /* Parcours de morceaux */
//     char* tex_filename_to_display=(char*)malloc((strlen(tex_filename)+nb_underscore)*sizeof(char));
    char* tex_filename_to_display[strlen(tex_filename)+2];
    tex_filename_to_display[0]= '\0';
    
    
    strcat(tex_filename_to_display, token);
    token = strtok(NULL, s);
    while( token != NULL ) 
    {
	strcat(tex_filename_to_display, "\\_");
	strcat(tex_filename_to_display, token);
	printf( "%s\n", token );
	
	token = strtok(NULL, s);
    }
    
    printf("NOM FIC : %s\n", tex_filename_to_display);
    
    // Write of LATEX instructions
    if (file != NULL)
    {
	fprintf(file, "\\documentclass{article}\n\\usepackage{pstricks}\n\\usepackage{pst-node}");
	fprintf(file, "\n\\usepackage[top=%s, bottom=%s, left=%s, right=%s]{geometry}\n", MARGE, MARGE, MARGE, MARGE);
	fprintf(file, "\\usepackage{graphics}\n");
	
	// TODO voir comment mettre le nom du fichier LATEX
	float total_weight;
	int nb;
	for(nb=0;nb< graphe->edges.nb_edges;nb++)
	{
		total_weight+=(get_edge(graphe->edges, nb))->cost;
		printf("Poids noeuds : %f\n", (get_edge(graphe->edges, nb))->cost);
	}
	fprintf(file, "\\begin{document}\n\\centering \\large{\\tt %s\nEdges sum : %f}\n",tex_filename_to_display, total_weight);
	fprintf(file, "\\scalebox{%s}{\n%% BEGIN GRAPHE\n", SCALING);
	
	graphe_to_latex(graphe, file, func_to_latex);
	
	fprintf(file, "\n}%% END GRAPHE\n\n\\end{document}");
	
	// File closed
	fclose(file);
    }
    else
    {
	// On affiche un message d'erreur
	printf("Impossible to create the output LATEX file\n");
    }
}

void full_graphe_to_latex_pdf(Graphe* graphe, char* filename)
{
    graphe_to_latex_pdf(graphe, filename, edges_to_latex);
}

void MST_to_latex_pdf(Graphe* g_mst, char* filename)
{
    graphe_to_latex_pdf(g_mst, filename, red_edges_to_latex);
}


