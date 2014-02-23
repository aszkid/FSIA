output.pdf: main.tex biblio/main.bib
	pdflatex -output-directory=out main.tex
	bibtex out/main.aux
	pdflatex -output-directory=out main.tex
	pdflatex -output-directory=out main.tex
