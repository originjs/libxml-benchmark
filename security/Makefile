include ../Makefile.in

ALLTARGETS = libxml libxml1 xerces-dom sun_dom2.class

HEADERS = tools.h ../tools/disp.h ../xmlgen/xmlgen.h ../xmlgen/opcgen.h ../xmlgen/random.h

CLASSES = bench.class

TARGETS = 


ifeq ($(XMLSEC1), yes)
TARGETS += libxml1
endif
ifeq ($(XMLSEC), yes)
TARGETS += libxml
endif
ifeq ($(SUN), yes)
TARGETS += sun_dom2.class
endif
ifeq ($(XSECURITY), yes)
TARGETS += xerces-dom
endif

all:	$(TARGETS)

clean:
	rm -f $(ALLTARGETS)  $(CLASSES)

libxml: libxml.c $(HEADERS)
	$(gcc) $< -o libxml $(XMLSEC_INCLUDE) $(XMLSEC_LIB) $(LIBS) $(FLAGS) 

libxml1: libxml1.c $(HEADERS) libxml1.h
	$(gcc) $< -o libxml1 $(XMLSEC1_INCLUDE) $(XMLSEC1_LIB) $(LIBS) $(FLAGS) 

xerces-dom: xerces-dom.cpp $(HEADERS) xerces-dom.h
	$(gpp) $< -o xerces-dom $(XSECURITY_INCLUDE) $(XSECURITY_LIB) $(LIBS) $(FLAGS)

sun_dom2.class: sun_dom2.java $(CLASSES)
	$(javac) -classpath $(SUN_CLASSPATH) $<

bench.class: bench.java
	$(javac) -classpath $(SUN_CLASSPATH) $<
