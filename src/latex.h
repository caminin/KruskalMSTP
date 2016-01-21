#include <stdio.h>
#include <stdlib.h>

#include "vertice.h"
#include "edge.h"


// TODO Florian : Penser à pscalebox {/*LATEX*/}
#define VERTICE_SPACE 0.22cm

FILE* to_latex(array_vertices vertices, array_edges edges, FILE* file);

void to_latex_pdf(array_vertices vertices, array_edges edges, FILE* file);

void to_latex_pdf_with_MST(array_vertices vertices, array_edges edges, array_edges MST, FILE* file);