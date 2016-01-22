#!/bin/sh

latex feuille.tex
dvips feuille.dvi
ps2pdf feuille.ps
evince feuille.pdf
