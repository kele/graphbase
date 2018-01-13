PDFLATEX=pdflatex

TEXFILES=thesis.tex wprowadzenie.tex architektura.tex jezyk-zapytan.tex

CHAPTERS=$(patsubst %.tex,%.pdf,${TEXFILES})


thesis.pdf: ${TEXFILES} iithesis.cls
	${PDFLATEX} thesis.tex
	# Rerun needed to get the bookmarks right
	${PDFLATEX} thesis.tex

.PHONY: chapters
chapters: ${CHAPTERS}

%.pdf: %.tex
	${PDFLATEX} $<
	# Rerun needed to get the bookmarks right
	${PDFLATEX} $<

clean:
	rm -rf *.pdf *.log *.out *.toc *.aux
