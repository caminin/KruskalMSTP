#!/bin/sh
LATEX_NAME="G.CHARLOT_Rodolphe"

echo "nom du fichier : "/LATEX_NAME

latex $LATEX_NAME.tex
dvips $LATEX_NAME.dvi
ps2pdf $LATEX_NAME.ps
evince $LATEX_NAME.pdf

rm $LATEX_NAME.aux
rm $LATEX_NAME.log
rm $LATEX_NAME.dvi
