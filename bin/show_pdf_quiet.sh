#!/bin/sh

latex -output-directory=./obj/ ./obj/feuille.tex -output-format=pdf >> ./obj/log.log
dvips -q ./obj/feuille.dvi -o ./obj/feuille.ps >> ./obj/log.log
ps2pdf ./obj/feuille.ps ./obj/feuille.pdf >> ./obj/log.log
evince ./obj/feuille.pdf >> ./obj/log.log
