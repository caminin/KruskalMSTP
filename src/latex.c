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

void edges_to_latex(void* ae, void* file)
{
    array_edges* _ae=(array_edges*)ae;
    // Edges export
    fprintf(file, "%% edges\n");
    int i;
    for (i= 0; i < _ae->nb_edges; ++i){
	    edge* e= get_edge(*_ae, i);
	    // Edges drawing TODO que fait le {-} ?
	    fprintf(file, "\\ncline{-}{%d}{%d}\n", e->first_v, e->second_v);
	    /// The cost of each edges is not displayed
    }
}

void red_edges_to_latex(void* ae, void* file)
{
    // Edges export
    array_edges* _ae=(array_edges*)ae;
    
    fprintf(file, "%% edges\n");
    int i;
    for (i= 0; i < _ae->nb_edges; ++i){
	edge* e= get_edge(*_ae, i);
	// Edges drawing TODO que fait le {-} ?
	fprintf(file, "\\ncline[linecolor=red,linewidth = 3pt]{-}{%d}{%d}\n", e->first_v, e->second_v);
	/// The cost of each edges is not displayed
    }
}

char graphe_to_latex(Graphe* graphe, FILE* file, void (*func_to_latex)(void* _ae, void* _file))
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
void graphe_to_latex_pdf(Graphe* graphe, FILE* file, void (*func_to_latex)(void* , void* ))
{
//     FILE* file= fopen(filename,"w");
    
    if (file != NULL)
    {
	    fprintf(file, "\\documentclass{article}\n\\usepackage{pstricks}\n\\usepackage{pst-node}");
	    fprintf(file, "\n\\usepackage[top=%s, bottom=%s, left=%s, right=%s]{geometry}\n", MARGE, MARGE, MARGE, MARGE);
	    fprintf(file, "\\usepackage{graphics}\n");
	
	    // TODO voir comment mettre le nom du fichier LATEX
	    float total_weight;
	    int nb;
	    for(nb=0;nb< graphe->vertices.nb_vertices;nb++)
	    {
		    total_weight+=(get_edge(graphe->edges, nb))->cost;
#ifdef DEBUG
		    printf("Poids noeuds : %f\n", (get_edge(graphe->edges, nb))->cost);
#endif
	    }
	    fprintf(file, "\\begin{document}\n\\centering \\large{\\tt Edges sum : %f}\n", total_weight);
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

void full_graphe_to_latex_pdf(Graphe* graphe, FILE* file)
{
    graphe_to_latex_pdf(graphe, file, edges_to_latex);
}

void MST_to_latex_pdf(Graphe* g_mst, FILE* file)
{
    graphe_to_latex_pdf(g_mst, file, red_edges_to_latex);
}


