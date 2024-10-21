include ../Makefile.in

TARGETS = opcgen xmlgen
ifeq ($(GENERATOR_XMARK),yes)
TARGETS += xmark xmarkdtd
endif


all: $(TARGETS)

clean:
	rm -rf $(TARGETS)

opcgen: opcgen.c opcgen.h random.h
	$(gcc) -o opcgen -lm $<

xmlgen: xmlgen.c xmlgen.h random.h
	$(gcc) -o xmlgen -lm $<

ifeq ($(GENERATOR_XMARK),yes)
xmark: xmark.c xmark.h unix.h
	$(gcc) -o xmark $<
ifeq ($(DTD_VALIDATION),yes)
xmarkdtd: xmarkdtd.c xmark.h unix.h
	$(gcc) -o xmarkdtd $<
endif
endif
