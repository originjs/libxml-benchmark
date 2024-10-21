include ../Makefile.in

ALLTARGETS = libxml libxml-sax libxml-push libxml-dom \
	expat expat-arabica-sax expat-arabica-dom \
	expat-cslxml-sax expat-cslxml-dom expat-sablotron-dom \
	xerces-sax xerces-dom xml4c-sax xml4c-dom \
	oracle-dom oracle-sax oracle-dom++ oracle-sax++ \
	rxp qt-sax qt-dom \
	sun_dom2.class sun_sax2.class oracle_dom2.class oracle_sax2.class \

ifeq ($(GENERATOR_XMARK),yes)
FLAGS+=-DGENERATOR_XMARK
endif

ifeq ($(DTD_VALIDATION),yes)
FLAGS+=-DDTD_VALIDATION
endif

TARGETS = 
ifeq ($(LIBXML), yes)
TARGETS += libxml libxml-push libxml-sax
ifeq ($(GDOME), yes)
TARGETS +=  libxml-dom
endif
endif

ifeq ($(EXPAT), yes)
TARGETS += expat
ifeq ($(ARABICA), yes)
TARGETS += expat-arabica-sax expat-arabica-dom
endif
ifeq ($(CSLXML), yes)
TARGETS += expat-cslxml-sax expat-cslxml-dom 
endif
ifeq ($(SABLOTRON), yes)
TARGETS += expat-sablotron-dom
endif
endif

ifeq ($(XERCESC), yes)
TARGETS += xerces-sax xerces-dom 
endif
ifeq ($(XML4C), yes)
TARGETS += xml4c-sax xml4c-dom
endif

ifeq ($(XDKC), yes)
TARGETS += oracle-dom oracle-sax
endif

ifeq ($(XDKP), yes)
TARGETS += oracle-dom++ oracle-sax++
endif

ifeq ($(RXP), yes)
TARGETS += rxp 
endif

ifeq ($(QT), yes)
TARGETS += qt-sax qt-dom
endif

ifeq ($(XDKJ), yes)
TARGETS += oracle_dom2.class oracle_sax2.class
endif
ifeq ($(SUN), yes)
TARGETS += sun_dom2.class sun_sax2.class 
endif

HEADERS = tools.h ../tools/disp.h ../xmlgen/xmlgen.h ../xmlgen/opcgen.h ../xmlgen/random.h

CLASSES = bench.class SaxHandlers.class

all: $(TARGETS)

clean:
	rm -f $(ALLTARGETS) $(CLASSES)

libxml: libxml.c $(HEADERS)
	$(gcc) $< -o libxml $(LIBXML_INCLUDE) $(LIBXML_LIB) $(LIBS) $(FLAGS)

libxml-push: libxml-push.c $(HEADERS)
	$(gcc) $< -o libxml-push $(LIBXML_INCLUDE) $(LIBXML_LIB) $(LIBS) $(FLAGS)

libxml-sax: libxml-sax.c $(HEADERS)
	$(gcc) $< -o libxml-sax $(LIBXML_INCLUDE) $(LIBXML_LIB) $(LIBS) $(FLAGS)

libxml-dom: libxml-dom.c $(HEADERS)
	$(gcc) $< -o libxml-dom $(GDOME_INCLUDE) $(GDOME_LIB) $(LIBS) $(FLAGS)

expat: expat.c $(HEADERS)
	$(gcc) $< -o expat $(EXPAT_INCLUDE) $(EXPAT_LIB) $(LIBS) $(FLAGS)

ifneq ($(XERCESC_VERSION), 2.1)
xerces-sax: xerces-sax.cpp $(HEADERS)
	$(gpp) $< -o xerces-sax $(XERCESC_INCLUDE) $(XERCESC_LIB) $(LIBS) $(FLAGS)

xerces-dom: xerces-dom.cpp $(HEADERS)
	$(gpp) $< -o xerces-dom $(XERCESC_INCLUDE) $(XERCESC_LIB) $(LIBS) $(FLAGS)
else
xerces-sax: xerces-sax.cpp $(HEADERS)
	$(compatgpp) $< -o xerces-sax $(XERCESC_INCLUDE) $(XERCESC_LIB) $(LIBS) $(FLAGS)

xerces-dom: xerces-dom.cpp $(HEADERS)
	$(compatgpp) $< -o xerces-dom $(XERCESC_INCLUDE) $(XERCESC_LIB) $(LIBS) $(FLAGS)
endif

ifneq ($(XML4C_VERSION), 5.0)
xml4c-sax: xerces-sax.cpp $(HEADERS)
	$(gpp)  $< -o xml4c-sax $(XML4C_INCLUDE) $(XML4C_LIB) $(LIBS) $(FLAGS)

xml4c-dom: xerces-dom.cpp $(HEADERS)
	$(gpp) $< -o xml4c-dom $(XML4C_INCLUDE) $(XML4C_LIB) $(LIBS) $(FLAGS)
else
xml4c-sax: xerces-sax.cpp $(HEADERS)
	$(compatgpp)  $< -o xml4c-sax $(XML4C_INCLUDE) $(XML4C_LIB) $(LIBS) $(FLAGS)

xml4c-dom: xerces-dom.cpp $(HEADERS)
	$(compatgpp) $< -o xml4c-dom $(XML4C_INCLUDE) $(XML4C_LIB) $(LIBS) $(FLAGS)
endif


rxp: rxp.c $(HEADERS)
	$(gcc) $< -o rxp $(RXP_INCLUDE) $(RXP_LIB) $(LIBS) $(FLAGS)

oracle-dom: oracle-dom.c $(HEADERS)
	$(gcc) $< -o oracle-dom $(XDKC_INCLUDE) $(XDKC_LIB) $(LIBS) $(FLAGS)

oracle-sax: oracle-sax.c $(HEADERS)
	$(gcc) $< -o oracle-sax $(XDKC_INCLUDE) $(XDKC_LIB) $(LIBS) $(FLAGS)

oracle-dom++: oracle-dom.cpp $(HEADERS)
	$(compatgpp) $< -o oracle-dom++ $(XDKP_INCLUDE) $(XDKP_LIB) $(LIBS) $(FLAGS)

oracle-sax++: oracle-sax.cpp $(HEADERS)
	$(compatgpp) $< -o oracle-sax++ $(XDKP_INCLUDE) $(XDKP_LIB) $(LIBS) $(FLAGS)

oracle_dom2.class: oracle_dom2.java $(CLASSES)
	$(javac) -classpath "$(ORACLE_CLASSPATH)" $< 

oracle_sax2.class: oracle_sax2.java $(CLASSES)
	$(javac) -classpath "$(ORACLE_CLASSPATH)" $< 

sun_sax2.class: sun_sax2.java $(CLASSES)
	$(javac) -classpath $(SUN_CLASSPATH) $< 

sun_dom2.class: sun_dom2.java $(CLASSES)
	$(javac) -classpath $(SUN_CLASSPATH) $< 

bench.class: bench.java
	$(javac) -classpath $(SUN_CLASSPATH) $<

SaxHandlers.class: SaxHandlers.java
	$(javac) -classpath $(SUN_CLASSPATH) $<

qt-sax: qt-sax.cpp $(HEADERS)
	$(gpp) $< $(QT_INCLUDE) $(QT_LIB)  -o qt-sax $(LIBS) $(FLAGS)

qt-dom: qt-dom.cpp $(HEADERS)
	$(gpp) $< $(QT_INCLUDE) $(QT_LIB) -o qt-dom $(LIBS) $(FLAGS)

expat-sablotron-dom: expat-sablotron-dom.cpp $(HEADERS)
	$(gpp) $< -o expat-sablotron-dom $(SABLOTRON_INCLUDE) $(SABLOTRON_LIB) $(LIBS) $(FLAGS)

expat-arabica-sax: expat-arabica-sax.cpp $(HEADERS)
	$(ARABICA_GCC)  $< -o expat-arabica-sax $(ARABICA_INCLUDE) $(ARABICA_LIB) $(LIBS) $(FLAGS)

expat-arabica-dom: expat-arabica-dom.cpp $(HEADERS)
	$(ARABICA_GCC)  $< -o expat-arabica-dom $(ARABICA_INCLUDE) $(ARABICA_LIB) $(LIBS) $(FLAGS)

expat-cslxml-sax: expat-cslxml-sax.cpp $(HEADERS)
	$(gppstd)  $< -o expat-cslxml-sax $(CSLXML_INCLUDE) $(CSLXML_LIB) $(LIBS) $(FLAGS)

expat-cslxml-dom: expat-cslxml-dom.cpp $(HEADERS)
	$(gppstd)  $< -o expat-cslxml-dom $(CSLXML_INCLUDE) $(CSLXML_LIB) $(LIBS) $(FLAGS)

fp_dom.class: fp_dom.java $(CLASSES)
	$(javac) -classpath $(FASTPARSER_CLASSPATH) $< 
