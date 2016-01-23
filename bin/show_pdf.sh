#!/bin/sh

latex -output-directory=./obj/ ./obj/feuille.tex 
dvips ./obj/feuille.dvi -o ./obj/feuille.ps
ps2pdf ./obj/feuille.ps ./obj/feuille.pdf
evince ./obj/feuille.pdf
