#ifndef LATEX_H
#define LATEX_H

#include <stdio.h>
#include <stdlib.h>

#include "vertice.h"
#include "edge.h"
#include "graphe.h"

// TODO Florian : Penser à pscalebox {/*LATEX*/}
#define VERTICE_SPACE 0.22cm


// Vertices export in LATEX
void vertices_to_latex(array_vertices*, FILE*);
void edges_to_latex(void* ae, void* file);
void red_edges_to_latex(void* ae, void* file);

char graphe_to_latex(Graphe* graphe, FILE* file, void (*func_to_latex)(void*, void*));

void graphe_to_latex_pdf(Graphe* graphe, char* filename, void (*edges_to_latex_func)(void* , void* ));
void full_graphe_to_latex_pdf(Graphe* graphe, char* filename);

void MST_to_latex_pdf(Graphe* g_mst, char* filename);

#endif
