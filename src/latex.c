#include "latex.h"

#define CIRCLE_RADIUS "1.0cm"
#define COEF_SIZE 5
#define SCALING "0.7"

char to_latex(array_vertices vertices, array_edges edges, FILE* file){
// 	file= fopen(filename,"w");
	
	if (file != NULL)
	{
	    fprintf(file, "\\begin{pspicture*}(-1,-1)(15,15)\n");
	    // Vertices export
	    fprintf(file, "%% vertices\n");
	    int i;
	    for (i= 0; i < vertices.nb_vertices; ++i){
		vertice* v= get_vertice(vertices, i);
		// Positioning of the vertice
		fprintf(file, "\\cnode(%d,%d)", COEF_SIZE * v->pos_x, COEF_SIZE *v->pos_y);
		// Size and number of the vertice
		fprintf(file, "{%s}{%d}", CIRCLE_RADIUS, i+1);
		// TODO Number positioning
		fprintf(file, "\\rput(%d,%d)", COEF_SIZE *v->pos_x, COEF_SIZE *v->pos_y);
		// TODO Number display
		fprintf(file, "{\\tt %d}\n", i+1);
	    }
	    
	    // Edges export
	    fprintf(file, "%% edges\n");
	    for (i= 0; i < edges.nb_edges; ++i){
		edge* e= get_edge(edges, i);
		// Edges drawing TODO que fait le {-} ?
		fprintf(file, "\\ncline{-}{%d}{%d}\n", e->first_v, e->second_v);
		/// The cost of each edges is not displayed
	    }
	    
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
void to_latex_pdf(array_vertices vertices, array_edges edges, FILE* file)
{
//     FILE* file= fopen(filename,"w");
    
    if (file != NULL)
    {
	fprintf(file, "\\documentclass{article}\n\\usepackage{pstricks}\n\\usepackage{pst-node}");
	fprintf(file, "\n\\usepackage[top=%s, bottom=%s, left=%s, right=%s]{geometry}\n", MARGE, MARGE, MARGE, MARGE);
	fprintf(file, "\\usepackage{graphics}\n");
	
	// TODO voir comment mettre le nom du fichier LATEX
	fprintf(file, "\\begin{document}\n\\centering \\large{\\tt %s}\n", "feuille.tex");
	fprintf(file, "\\scalebox{%s}{\n%% BEGIN GRAPHE\n", SCALING);
	
	to_latex(vertices, edges, file);
	
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
