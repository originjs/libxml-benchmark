include ../Makefile.in

ALLTARGETS = libxml xml4c-dom expat-sablotron-dom oracle-dom sun_dom2.class \
	xerces-dom

TARGETS =

ifeq ($(LIBXSLT), yes)
TARGETS += libxml
endif

ifeq ($(XALANC), yes)
TARGETS += xerces-dom 
endif

ifeq ($(LOTUSXSL), yes)
TARGETS += xml4c-dom
endif

ifeq ($(XDKC), yes)
TARGETS += oracle-dom
endif

ifeq ($(SABLOTRON), yes)
TARGETS += expat-sablotron-dom
endif

ifeq ($(SUN), yes)
TARGETS += sun_dom2.class
endif


HEADERS = tools.h tools2.h ../tools/disp.h ../xmlgen/xmlgen.h ../xmlgen/opcgen.h ../xmlgen/random.h

CLASSES = bench.class

all:	$(TARGETS)

clean:
	rm -f $(ALLTARGETS) $(CLASSES)

libxml: libxml.c $(HEADERS)
	$(gcc) -o libxml $(LIBXSLT_INCLUDE) $(LIBXSLT_LIB) $(LIBS) $(FLAGS) $<

ifneq ($(XERCESC_VERSION), 2.1)
xerces-dom: xerces-dom.cpp $(HEADERS) 
	$(gpp) $< -o xerces-dom $(XALANC_INCLUDE) $(XALANC_LIB) $(LIBS) $(FLAGS)
else
xerces-dom: xerces-dom.cpp $(HEADERS) 
	$(compatgpp) $< -o xerces-dom $(XALANC_INCLUDE) $(XALANC_LIB) $(LIBS) $(FLAGS)
endif

ifneq ($(XML4C_VERSION), 5.0)
xml4c-dom: xerces-dom.cpp $(HEADERS) 
	$(gpp) $< -o xml4c-dom $(LOTUSXSL_INCLUDE) $(LOTUSXSL_LIB) $(LIBS) $(FLAGS)
else
xml4c-dom: xerces-dom.cpp $(HEADERS) 
	$(compatgpp) $< -o xml4c-dom $(LOTUSXSL_INCLUDE) $(LOTUSXSL_LIB) $(LIBS) $(FLAGS)
endif

expat-sablotron-dom: expat-sablotron-dom.cpp $(HEADERS)
	$(gpp)  $< -o expat-sablotron-dom $(SABLOTRON_INCLUDE) $(SABLOTRON_LIB) $(LIBS) $(FLAGS)

oracle-dom: oracle-dom.c $(HEADERS)
	$(gcc) $< -o oracle-dom $(XDKC_INCLUDE) $(XDKC_LIB) $(LIBS) $(FLAGS)

sun_dom2.class: sun_dom2.java $(CLASSES)
	$(javac) -classpath $(SUN_CLASSPATH) $< 

bench.class: bench.java
	$(javac) -classpath $(SUN_CLASSPATH) $<
