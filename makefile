LATEXMK = latexmk -pdf -cd -interaction=nonstopmode -halt-on-error

DIRS    := teoria practicas
MAINS   := $(wildcard $(addsuffix /main.tex,$(DIRS)))
SUBDIRS := $(wildcard $(addsuffix /*/,$(DIRS)))
SUBS    := $(foreach d,$(SUBDIRS),$(wildcard $(d)$(notdir $(d:%/=%)).tex))

MAIN_PDFS := $(MAINS:.tex=.pdf)
SUB_PDFS  := $(SUBS:.tex=.pdf)
ALL_PDFS  := $(MAIN_PDFS) $(SUB_PDFS)

.PHONY: all practicas teoria mains clean distclean

all: $(ALL_PDFS) examenes

practicas: $(filter practicas/%,$(ALL_PDFS))

teoria: $(filter teoria/%,$(ALL_PDFS))

mains: $(MAIN_PDFS)

examenes:
	$(MAKE) -C examenes

# Rebuild the full books whenever any chapter file inside their subdirectories changes
practicas/main.pdf: $(wildcard practicas/*/*.tex)
teoria/main.pdf: $(wildcard teoria/*/*.tex)

%.pdf: %.tex
	$(LATEXMK) $*.tex

clean:
	@for f in $(MAINS) $(SUBS); do latexmk -c -cd "$$f"; done

distclean:
	@for f in $(MAINS) $(SUBS); do latexmk -C -cd "$$f"; done