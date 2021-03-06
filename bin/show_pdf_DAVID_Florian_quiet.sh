#!/bin/sh
LATEX_NAME="G.DAVID_Florian"

echo "nom du fichier : "LATEX_NAME

mkdir obj

latex -output-directory=./obj/ $LATEX_NAME.tex -output-format=pdf >> ./obj/log.log
dvips -q ./obj/$LATEX_NAME.dvi -o ./obj/$LATEX_NAME.ps >> ./obj/log.log
ps2pdf ./obj/$LATEX_NAME.ps ./obj/$LATEX_NAME.pdf >> ./obj/log.log
evince ./obj/$LATEX_NAME.pdf >> ./obj/log.log
