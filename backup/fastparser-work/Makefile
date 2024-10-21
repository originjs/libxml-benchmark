javac = javac
FASTPARSER_CLASSPATH = .:../tools:/usr/java/fp/fp-dom.jar:/usr/java/fp/fp-parser.jar:/usr/java/fp/dom.jar:$(CLASSPATH)

TARGETS = fp_dom.class
CLASSES = bench.class

LIBS = -lm 

all: $(TARGETS)

clean:
	rm -f $(TARGETS) $(CLASSES)

bench.class: bench.java
	$(javac) -classpath $(SUN_CLASSPATH) $<

fp_dom.class: fp_dom.java $(CLASSES)
	$(javac) -classpath $(FASTPARSER_CLASSPATH) $< 
