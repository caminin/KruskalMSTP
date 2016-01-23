#!/bin/sh

latex -output-directory=./obj/ ./obj/feuille.tex -output-format=pdf
dvips -q ./obj/feuille.dvi -o ./obj/feuille.ps
ps2pdf ./obj/feuille.ps ./obj/feuille.pdf
evince ./obj/feuille.pdf
