output.pdf: main.tex
	pdflatex -output-directory=out main.tex
	biber out/main
	pdflatex -output-directory=out main.tex
