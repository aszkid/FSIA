final.pdf: test.tex biblios/biblio.bib biblios/biblio_gonzalo.bib
	pdflatex -output-directory=output test.tex
	bibtex output/test.aux
	pdflatex -output-directory=output test.tex
	pdflatex -output-directory=output test.tex
