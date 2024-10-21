include ../Makefile.in

ALLTARGETS = xerces-dom xml4c-dom oracle-dom libxml sun_dom2.class

TARGETS = 

ifeq ($(LIBXML), yes)
TARGETS += libxml
endif

ifeq ($(XERCESC), yes)
TARGETS += xerces-dom 
endif
ifeq ($(XML4C), yes)
TARGETS += xml4c-dom
endif

ifeq ($(XDKC), yes)
TARGETS += oracle-dom
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
	$(gcc) $< -o libxml $(LIBXML_INCLUDE) $(LIBXML_LIB) -lxml2

ifneq ($(XERCESC_VERSION), 2.1)
xerces-dom: xerces-dom.cpp $(HEADERS) tools/xerces/DOMTreeErrorReporter.cpp tools/xerces/DOMTreeErrorReporter.hpp
	$(gpp) $< tools/xerces/DOMTreeErrorReporter.cpp -o xerces-dom $(XERCESC_INCLUDE) $(XERCESC_LIB) $(LIBS) $(FLAGS) -I./tools/xerces
else
xerces-dom: xerces-dom.cpp $(HEADERS) tools/xerces/DOMTreeErrorReporter.cpp tools/xerces/DOMTreeErrorReporter.hpp
	$(compatgpp) $< tools/xml4c/DOMTreeErrorReporter.cpp -o xerces-dom $(XERCESC_INCLUDE) $(XERCESC_LIB)  $(LIBS) $(FLAGS) -I./tools/xml4c
endif

ifneq ($(XML4C_VERSION), 5.0)
xml4c-dom: xerces-dom.cpp $(HEADERS) tools/xml4c/DOMTreeErrorReporter.cpp tools/xml4c/DOMTreeErrorReporter.hpp
	$(gpp) $< tools/xerces/DOMTreeErrorReporter.cpp -o xml4c-dom $(XML4C_INCLUDE) $(XML4C_LIB)  $(LIBS) $(FLAGS) -I./tools/xerces
else
xml4c-dom: xerces-dom.cpp $(HEADERS) tools/xml4c/DOMTreeErrorReporter.cpp tools/xml4c/DOMTreeErrorReporter.hpp
	$(compatgpp) $< tools/xml4c/DOMTreeErrorReporter.cpp -o xml4c-dom $(XML4C_INCLUDE) $(XML4C_LIB)  $(LIBS) $(FLAGS) -I./tools/xml4c
endif

oracle-dom: oracle-dom.c $(HEADERS)
	$(gcc) $< -o oracle-dom $(XDKC_INCLUDE) $(XDKC_LIB_VALIDATE) $(LIBS) $(FLAGS) 

sun_dom2.class: sun_dom2.java $(CLASSES)
	$(javac) -classpath $(SUN_CLASSPATH) $< 

bench.class: bench.java
	$(javac) -classpath $(SUN_CLASSPATH) $<
