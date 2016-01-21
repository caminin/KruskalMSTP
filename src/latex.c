#include "edge.h"
#include "vertice.h"

#define VERTICE_SPACE 0.22cm
char to_latex(array_vertices vertices, array_edges edges, FILE* file){
// 	file= fopen(filename,"w");
	
	if (file != NULL)
	{
	    fprintf(file, "\\begin{pspicture*}(0,0)(50,50)\n");
	    // Vertices export
	    fprintf(file, "%% vertices\n");
	    for (int i= 0; i < vertices.nb_vertices; ++i){
		vertice* v= vertices.at(i);
		// Positioning of the vertice
		fprintf(file, "\\cnode(%d,%d)", v->pox_x, v->pox_y);
		// Size and number of the vertice
		fprintf(file, "{VERTICE_SPACE}{%d}", i+1);
		// TODO ??? que fait \rput, identique à \cnode
		fprintf(file, "\\rput(%d,%d)", v->pox_x, v->pox_y);
		// TODO ??? que fait \tt, identique à au numéro
		fprintf(file, "{\\tt %d}\n", i+1);
	    }
	    
	    // Edges export
	    fprintf(file, "%% edges\n");
	    for (int i= 0; i < edges.nb_edges; ++i){
		edge* e= edges.at(i);
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

#define MARGE 2cm
void to_latex_pdf(array_vertices vertices, array_edges edges, FILE* file)
{
//     FILE* file= fopen(filename,"w");
    
    if (file != NULL)
    {
	fprintf(file, "\\documentclass{article}\n\\usepackage{pstricks}\n\\usepackage{pst-node}");
	fprintf(file, "\n\\usepackage[top=MARGE, bottom=MARGE, left=MARGE, right=MARGE]{geometry}\n");
	// TODO voir comment mettre le nom du fichier LATEX
	fprintf(file, "\\begin{document}\n\\centering \\large{\\tt %s}\n", "exemple_feuille.tex");
	fprintf(file, "pscalebox{0.25}{\n%% BEGIN GRAPHE\n");
	
	to_latex(vertices, edges, file);
	
	fprintf(file, "}%% END GRAPHE\n\n\\end{document}");
	
	// File closed
	fclose(file);
    }
    else
    {
	// On affiche un message d'erreur
	printf("Impossible to create the output LATEX file\n");
    }
}
