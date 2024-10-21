#include <libxml/xmlreader.h>

    if (!reader) {
	reader = xmlReaderForDoc(td->xml, "xml", NULL, 0);
	if (!reader) {
    	    printf("Error creating new xmlReader!\n");
    	    exit(0);
	}
    } else {
	err = xmlReaderNewDoc(reader, td->xml, "xml", NULL, 0);
	if (err) {
    	    printf("Error reinitializing xmlReader!\n");
    	    exit(0);
	}
    }
    err = xmlTextReaderRead(reader);
    if (err!=1) {
        printf("Error parsing document (xmlTextReaderRead)!\n");
        exit(0);
    }
    
    node = xmlTextReaderExpand(reader);
    if (!node) {
	puts("bl");
	exit(0);
    }
/*
    while (err == 1) {
	
	err = xmlTextReaderRead(reader);
    }
*/
    
    doc = xmlTextReaderCurrentDoc(reader);


----------
xmlTextReaderPtr reader = NULL;
----------
if (reader) xmlFreeTextReader(reader);
----------

