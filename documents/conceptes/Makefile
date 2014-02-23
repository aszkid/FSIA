final.pdf: main.tex biblios/biblio.bib biblios/biblio_gonzalo.bib
	pdflatex -output-directory=output main.tex
	bibtex output/main.aux
	pdflatex -output-directory=output main.tex
	pdflatex -output-directory=output main.tex
