LATEX=pdflatex

TEXFILES=thesis.tex wprowadzenie.tex architektura.tex

thesis.pdf: ${TEXFILES} iithesis.cls
	pdflatex thesis.tex
	# Rerun needed to get the bookmarks right
	pdflatex thesis.tex

clean:
	rm -rf *.pdf *.log *.out *.toc *.aux
