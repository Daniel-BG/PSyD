FILENAME = main

.PHONY: all questions solutions clean

all: questions solutions

# Versión para alumnos (solo preguntas)
questions:
	latexmk -pdf -jobname=$(FILENAME)_preguntas $(FILENAME).tex

# Versión para profesores (preguntas + soluciones)
solutions:
	latexmk -pdf -jobname=$(FILENAME)_soluciones -pdflatex='pdflatex %O "\def\showsolutions{1}\input{%S}"' $(FILENAME).tex

# Limpieza de archivos auxiliares y PDFs generados
clean:
	latexmk -C
	rm -f *.sol *.toc *.aux *.log *.out *_preguntas.pdf *_soluciones.pdf