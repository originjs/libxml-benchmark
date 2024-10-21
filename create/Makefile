include ../Makefile.in

ALLTARGETS = libxml libxml-dom expat-cslxml-dom expat-sablotron-dom \
	xerces-dom xml4c-dom oracle-dom oracle-dom++ qt-dom \
	sun_dom2.class oracle_dom2.class

TARGETS = 

ifeq ($(LIBXML), yes)
TARGETS += libxml
ifeq ($(GDOME), yes)
TARGETS +=  libxml-dom
endif
endif

ifeq ($(CSLXML), yes)
TARGETS += expat-cslxml-dom 
endif
ifeq ($(SABLOTRON), yes)
TARGETS += expat-sablotron-dom
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
ifeq ($(XDKP), yes)
TARGETS += oracle-dom++
endif

ifeq ($(QT), yes)
TARGETS += qt-dom
endif

ifeq ($(XDKJ), yes)
TARGETS += oracle_dom2.class
endif
ifeq ($(SUN), yes)
TARGETS += sun_dom2.class
endif

HEADERS = tools.h ../tools/disp.h
CLASSES = bench.class

all:	$(TARGETS)

clean:
	rm -f $(ALLTARGETS) $(CLASSES)

libxml: libxml.c $(HEADERS)
	$(gcc) $< -o libxml $(LIBXML_INCLUDE) $(LIBXML_LIB) $(LIBS) $(FLAGS)

libxml-dom: libxml-dom.c $(HEADERS)
	$(gcc) $< -o libxml-dom $(GDOME_INCLUDE) $(GDOME_LIB) $(LIBS) $(FLAGS)

ifneq ($(XERCESC_VERSION), 2.1)
xerces-dom: xerces-dom.cpp $(HEADERS)
	$(gpp) $< -o xerces-dom $(XERCESC_INCLUDE) $(XERCESC_LIB) -I./tools/xerces $(LIBS) $(FLAGS)
else
xerces-dom: xerces-dom.cpp $(HEADERS)
	$(compatgpp) $< -o xerces-dom $(XERCESC_INCLUDE) $(XERCESC_LIB) -I./tools/xml4c $(LIBS) $(FLAGS)
endif

ifneq ($(XML4C_VERSION), 5.0)
xml4c-dom: xerces-dom.cpp $(HEADERS)
	$(gpp) $< -o xml4c-dom $(XML4C_INCLUDE) $(XML4C_LIB) -I./tools/xerces $(LIBS) $(FLAGS)
else
xml4c-dom: xerces-dom.cpp $(HEADERS)
	$(compatgpp) $< -o xml4c-dom $(XML4C_INCLUDE) $(XML4C_LIB) -I./tools/xml4c $(LIBS) $(FLAGS)
endif

oracle-dom: oracle-dom.c $(HEADERS)
	$(gcc) $< -o oracle-dom $(XDKC_INCLUDE) $(XDKC_LIB)  $(LIBS) $(FLAGS)

oracle-dom++: oracle-dom.cpp $(HEADERS)
	$(compatgpp) $< -o oracle-dom++ $(XDKP_INCLUDE) $(XDKP_LIB) $(LIBS) $(FLAGS)

oracle_dom2.class: oracle_dom2.java $(CLASSES)
	$(javac) -classpath "$(ORACLE_CLASSPATH)" $< 

sun_dom2.class: sun_dom2.java $(CLASSES)
	$(javac) -classpath $(SUN_CLASSPATH) $< 

bench.class: bench.java
	$(javac) -classpath $(SUN_CLASSPATH) $<

qt-dom: qt-dom.cpp $(HEADERS)
	$(gpp) $< $(QT_INCLUDE) $(QT_LIB) -o qt-dom $(LIBS) $(FLAGS)

expat-sablotron-dom: expat-sablotron-dom.cpp $(HEADERS)
	$(gpp) $< -o expat-sablotron-dom $(SABLOTRON_INCLUDE) $(SABLOTRON_LIB) $(LIBS) $(FLAGS)

expat-cslxml-dom: expat-cslxml-dom.cpp $(HEADERS)
	$(gppstd)  $< -o expat-cslxml-dom $(CSLXML_INCLUDE) $(CSLXML_LIB) $(LIBS) $(FLAGS)
